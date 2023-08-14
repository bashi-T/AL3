#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"Player.h"

class Enemy;

class Enemy
{
public:
	Enemy();
	~Enemy();

	void ChangeState(BaseEnemyState*newState);

	void Initialise(Model* model);

	void Update();

	void translateZ(float EnemySpeedZ);

	void Approach();

	void Leave();

	void Draw(const ViewProjection& viewProjection);

	WorldTransform GetWorldTransform() { return worldTransform_; }

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
	//static void (Enemy::*spFuncTable[])();
	BaseEnemyState* state_;

	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};

class BaseEnemyState 
{
	void Update();

	virtual void Approach(Enemy* pEnemy);

	virtual void Leave(Enemy* pEnemy);

	void ShowState();

//private:
	Enemy* enemy_;
};

class EnemyStateApproach : public BaseEnemyState
{
public:
	void Update();
};

class EnemyStateLeave : public BaseEnemyState
{
public:
	void Update();
};