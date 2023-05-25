#include "PlayerBullet.h"
#include"cassert"

void PlayerBullet::Initialise(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("takion.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = { position.x,position.y,position.z };
}

void PlayerBullet::Update()
{
	worldTransform_.UpdateMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
