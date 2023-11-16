#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"
#include<Input.h>
#include"ImGuiManager.h"
#include"list"
#include"EnemyBullet.h"
#include<random>

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

	void MoveRand();

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

	static const int kFireInterval = 64;
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	void SetPlayer(Player* player) { player_ = player; }
	bool IsDead() const { return isDead_; }
	void SetIsDiscover();
	int32_t GetIsDiscover() { return IsDiscover; }

private:
	//EnemyBullet* bullet_ = nullptr;
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
	bool isDead_ = false;
	float enemySpeed = 0.25f;
	Vector3 distXYZ;
	int32_t mapsize = 3;
	int32_t stayTimer = 120;
	int32_t distinationX;
	int32_t distinationZ;
	int32_t IsDiscover = 0;
	int32_t seekCount = 300;
	
	struct Sight {

	};
};

