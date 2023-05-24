#pragma once
#include"Model.h"
#include"ViewProjection.h"

class PlayerBullet
{
public:
	void Initialise(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;


};

