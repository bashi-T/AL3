#include "PlayerBullet.h"

void PlayerBullet::Initialise(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("glass.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = { position.x,position.y,position.z };
	velocity_ = velocity;
}

void PlayerBullet::Update()
{
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;
	worldTransform_.UpdateMatrix();
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void PlayerBullet::OnCollition()
{ isDead_ = true; }
