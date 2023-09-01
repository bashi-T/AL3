#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"
#include<Input.h>
#include"ImGuiManager.h"
#include"list"
#include"EnemyBullet.h"

class Player;
class GameScene;
class Enemy
{
public:

	~Enemy();
	void Initialise(Model* model, Vector3 translate);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Approach();

	void Leave();

	void Fire();
	
	void ResetApproach();

	Vector3 GetWorldPosition();

		void OnCollition();

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

	static const int kFireInterval = 64;
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	void SetPlayer(Player* player) { player_ = player; }
	bool IsDead() const { return isDead_; }
	bool isDead_ = false;

private:
	GameScene* gameScene_ = nullptr;
	Player* player_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	int32_t FireTimer = 1;
	float kEnemySpeedX = 0.0f;
	float kEnemySpeedY = 0.0f;
	float kEnemySpeedZ = 0.0f;
};

