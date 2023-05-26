#pragma once
#include "ViewProjection.h"
#include "Model.h"
#include "WorldTransform.h"
#include<Input.h>
#include"PlayerBullet.h"
#include"list"
class Player {
public:
	~Player();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	void Initialize(Model* model, uint32_t textureHandle);
	
	/// <summary>
	/// 
	/// </summary>
	void Update();
	
	void Rotate();

	void Attack();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	std::list<PlayerBullet*>bullets_;

private:
	PlayerBullet* bullet_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float inputFloat3[3] = { 0,0,0 };
};
