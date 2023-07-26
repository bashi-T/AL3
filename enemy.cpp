#include "enemy.h"
#include "Player.h"

Enemy::~Enemy()
{
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Enemy::Initialise(Model* model) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("sand.png");
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = {0, 10, 100};
	ResetApproach();
}

void Enemy::Update() {
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	
	const float kBulletSpeedZ = -0.5f;
	Vector3 velocity(0, 0, kBulletSpeedZ);

	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
	worldTransform_.UpdateMatrix();
	FireTimer--;
	if (FireTimer == 0) {
		Fire();
		FireTimer = kFireInterval;
	}
	if (bullet_) {
		bullet_->Update();
	}
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Approach() {
	kEnemySpeedZ = -0.5f;
	worldTransform_.translation_.x += kEnemySpeedX;
	worldTransform_.translation_.y += kEnemySpeedY;
	worldTransform_.translation_.z += kEnemySpeedZ;
	if (worldTransform_.translation_.z < 20.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	kEnemySpeedZ = 0.5f;
	worldTransform_.translation_.x += kEnemySpeedX;
	worldTransform_.translation_.y += kEnemySpeedY;
	worldTransform_.translation_.z += kEnemySpeedZ;
	if (worldTransform_.translation_.z > 120.0f) {
		phase_ = Phase::Approach;
	}
}

void Enemy::Fire() {
	assert(player_);
	float kBulletSpeedX = -1.0f;
	float kBulletSpeedY = -1.0f;
	float kBulletSpeedZ = -1.0f;
	player_->GetWorldPosition();
	GetWorldPosition();
	Vector3 direction = Subtract( player_->GetWorldPosition(),GetWorldPosition());
	kBulletSpeedX = Normalize(direction).x;
	kBulletSpeedY = Normalize(direction).y;
	kBulletSpeedZ = Normalize(direction).z;
	Vector3 velocity(kBulletSpeedX, kBulletSpeedY, kBulletSpeedZ);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialise(model_, worldTransform_.translation_, velocity);
	bullets_.push_back(newBullet);
}

void Enemy::ResetApproach() {
	FireTimer = 10; }

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollition() {}
