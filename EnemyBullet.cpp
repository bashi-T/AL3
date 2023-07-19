#include "EnemyBullet.h"

void EnemyBullet::Initialise(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("renga.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {position.x, position.y, position.z};
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void EnemyBullet::OnCollition() { isDead_ = true; }
