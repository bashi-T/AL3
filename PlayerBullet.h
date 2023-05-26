#pragma once
#include"Model.h"
#include"ViewProjection.h"

class PlayerBullet
{
public:
	void Initialise(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	Vector3 velocity_;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;


};

