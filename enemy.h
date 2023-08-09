#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"Player.h"

class Enemy
{
public:
	void Initialise(Model* model);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Approach();

	void Leave();

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	static void (Enemy::*spFuncTable[])();

	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};

