#include"Player.h"

Player::~Player()
{
	for (PlayerBullet* bullet : bullets_)
	{
	   delete bullet;
	}
}
void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 playerPosition) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	ReticleModel_ = model;
	ReticleTextureHandle_ = TextureManager::Load("JunglePocket.png");
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.matWorld_.m[3][0] = playerPosition.x;
	worldTransform_.matWorld_.m[3][1] = playerPosition.y;
	worldTransform_.matWorld_.m[3][2] = playerPosition.z;
	worldTransform3Dreticle_.Initialize();
};



void Player::Update() {
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Translate();

	Rotate();

	worldTransform_.UpdateMatrix();

	ImGui::Begin("player");
	inputWorld3[0] = worldTransform_.matWorld_.m[3][0];
	inputWorld3[1] = worldTransform_.matWorld_.m[3][1];
	inputWorld3[2] = worldTransform_.matWorld_.m[3][2];
	ImGui::InputFloat3("world", inputWorld3);
	inputtranslate3[0] = worldTransform_.translation_.x;
	inputtranslate3[1] = worldTransform_.translation_.y;
	inputtranslate3[2] = worldTransform_.translation_.z;
	ImGui::InputFloat3("translation", inputtranslate3);
	ImGui::End();

	worldTransform_.matWorld_.m[3][0] =
	    max(worldTransform_.matWorld_.m[3][0], -kMoveLimitX);
	worldTransform_.matWorld_.m[3][0] =
	    min(worldTransform_.matWorld_.m[3][0], +kMoveLimitX);
	worldTransform_.matWorld_.m[3][1] =
		max(worldTransform_.matWorld_.m[3][1], -kMoveLimitY);
	worldTransform_.matWorld_.m[3][1] =
		min(worldTransform_.matWorld_.m[3][1], +kMoveLimitY);

	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0, 0, 1.0f};
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset = Multiply(kDistancePlayerTo3DReticle ,Normalize(offset));
	worldTransform3Dreticle_.translation_ = Transform(offset, worldTransform_.matWorld_);
	worldTransform3Dreticle_.UpdateMatrix();

	Attack();
	for (PlayerBullet* bullet : bullets_) {
	   bullet->Update();
	}
}

void Player::Translate()
{
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.4f;

	if (input_->PushKey(DIK_LEFT))
	{
	   move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
	   move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP))
	{
	   move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN))
	{
	   move.y -= kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	//worldTransform_.translation_.z += move.z;
}

void Player::Rotate()
{
	const float kRotSpeed = 0.02f;
	if (input_->PushKey(DIK_Q))
	{
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_R))
	{
		worldTransform_.rotation_.y += kRotSpeed;
	}
}
void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE))
	{
		FireTimer--;
		if (FireTimer == 0)
		{
			FireTimer = 10;
			const float kBulletSpeedZ = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeedZ);
			velocity.x =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][0];
			velocity.y =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][1];
			velocity.z =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][2];
			velocity = Multiply(kBulletSpeedZ, Normalize(velocity));
			PlayerBullet* newBullet = new PlayerBullet();
			newBullet->Initialise(
				model_,
				worldTransform_.matWorld_,
				velocity);
			bullets_.push_back(newBullet);
		}
	} else {
		FireTimer = 1;
	}
}

void Player::OnCollition()
{

}

void Player::SetParent(const WorldTransform* parent)
{
	worldTransform_.parent_ = parent;
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
};

void Player::Draw(ViewProjection viewProjection_)
{
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	for (PlayerBullet* bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
	ReticleModel_->Draw(worldTransform3Dreticle_, viewProjection_, ReticleTextureHandle_);
};