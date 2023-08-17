#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"Player.h"

class Enemy;

class BaseEnemyState 
{
public:
	virtual void Update() = 0;

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

class Enemy {
public:
	Enemy();
	~Enemy();

	void ChangeState(BaseEnemyState* newState);

	void Initialise(Model* model);

	void Update();

	void translateZ(float EnemySpeedZ);

	void Approach();

	void Leave();

	void Draw(const ViewProjection& viewProjection);

	float GetWTtranslationZ() { return worldTransform_.translation_.z; }

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
	BaseEnemyState* state_;

	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};
