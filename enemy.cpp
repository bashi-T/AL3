#include "enemy.h"

void Enemy::Initialise(Model* model)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("sand.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,5,100 };
}

void Enemy::Update()
{
	const float kBulletSpeedZ = -0.5f;
	Vector3 velocity(0, 0, kBulletSpeedZ);
	//worldTransform_.translation_.x += velocity.x;
	//worldTransform_.translation_.y += velocity.y;
	worldTransform_.translation_.z += velocity.z;
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
