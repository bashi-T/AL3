#include "enemy.h"
#include<iostream>

Enemy::Enemy()
{
	state_ = new EnemyStateApproach();
}

Enemy::~Enemy()
{
	delete state_;
}

void Enemy::ChangeState(BaseEnemyState* newState)
{
	delete state_;
	state_ = newState;
}

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
	state_->Update();

	worldTransform_.UpdateMatrix();

}

void Enemy::translateZ(float EnemySpeedZ)
{
	worldTransform_.translation_.z += EnemySpeedZ;
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Approach() {
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	kEnemySpeedZ = 0.5f;
	worldTransform_.translation_.x += kEnemySpeedX;
	worldTransform_.translation_.y += kEnemySpeedY;
	worldTransform_.translation_.z += kEnemySpeedZ;
	if (worldTransform_.translation_.z > 100.0f) {
		phase_ = Phase::Approach;
	}
}

void EnemyStateApproach::Update()
{
	enemy_->translateZ(-0.5f);
}

void EnemyStateLeave::Update()
{
	enemy_->translateZ(0.5f);
}

void BaseEnemyState::Update()
{
	if (enemy_->GetWTtranslationZ() >= 120.0f)
	{
		enemy_->ChangeState(new EnemyStateApproach);
	}
	if (enemy_->GetWTtranslationZ() <= 20.0f)
	{
		enemy_->ChangeState(new EnemyStateLeave);
	}
}
