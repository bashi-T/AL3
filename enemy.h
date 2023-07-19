#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"
#include<Input.h>
#include"ImGuiManager.h"
#include"list"
#include"EnemyBullet.h"

class Player;

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

	Vector3 GetWorldPosition();

		void OnCollition();

	void SetPlayer(Player* player) { player_ = player; }
	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

	std::list<EnemyBullet*> bullets_;
	static const int kFireInterval = 64;
	const std::list<EnemyBullet*> GetBullets() const { return bullets_; }

private:
	EnemyBullet* bullet_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;
	Input* input_ = nullptr;
	int32_t FireTimer = 1;
	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};

