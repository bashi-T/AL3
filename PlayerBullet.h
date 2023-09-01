#pragma once
#include"Model.h"
#include"ViewProjection.h"

class PlayerBullet
{
public:
	void Initialise(Model* model, const Matrix4x4& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	void OnCollition();
	Vector3 GetWorldPosition();
	Vector3 velocity_ = {0};
	bool IsDead()const { return isDead_; }
	bool isDead_ = false;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	int32_t deathTimer_ = kLifeTime;
	static const int32_t kLifeTime = 60 * 5;
};

