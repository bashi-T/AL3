#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include"Player.h"

class Enemy
{
public:
	void Initialise(Model* model);

	void Update();

	void Draw(const ViewProjection& viewProjection);



private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Player* player_ = nullptr;

};

