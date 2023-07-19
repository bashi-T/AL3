#pragma once
#include"Model.h"
#include"ViewProjection.h"

class PlayerBullet
{
public:
	void Initialise(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void OnCollition();
	Vector3 velocity_;
	bool IsDead()const { return isDead_; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
	static const int32_t kLifeTime = 60 * 5;


};

