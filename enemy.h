#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Model.h"
#include<Input.h>
#include"ImGuiManager.h"
#include"list"
#include"EnemyBullet.h"
#include<random>
#include"ALVector.h"
#include<DirectXMath.h>
#include "Player.h"

class Enemy {
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

	void SetSight();

	void SetRadian();

	enum class Phase {
		Approach,
		Leave,
	};
	Phase phase_ = Phase::Approach;

	static const int kFireInterval = 64;
	// void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
	void SetPlayer(Player* player) { player_ = player; }
	bool IsDead() const { return isDead_; }
	void SetIsDiscover(int i);
	void SetDiscoverCount(int i);
	void SetSeekCount(int i);

	int32_t GetIsDiscover() { return IsDiscover; }
	int32_t GetDiscoverCount() { return DiscoverCount; }
	int32_t GetSeekCount() { return seekCount; }

private:
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
	int IsDiscover = 0;
	int DiscoverCount = 900;
	int32_t seekCount = 300;
	float theta_ = 3.1415926535f;
	struct Sight {
		Vector3 SightLeft{};
		Vector3 SightRight{};
		float radian = 0.0f;
		float baseRadian = 0.0f;
		float range = 50.0f;
	} sight;

public:
	Sight GetSight() { return sight; }
};

