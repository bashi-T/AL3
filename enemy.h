#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"
#include"Player.h"
#include<Input.h>
#include"ImGuiManager.h"
#include"list"
#include"EnemyBullet.h"

class Enemy
{
public:

	~Enemy();
	void Initialise(Model* model);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Approach();

	void Leave();

	void Fire();
	
	void ResetApproach();

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

	std::list<EnemyBullet*> bullets_;
	static const int kFireInterval = 60;

private:
	EnemyBullet* bullet_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	Input* input_ = nullptr;
	int32_t FireTimer = 0;
	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};

