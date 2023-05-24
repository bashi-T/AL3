#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<Input.h>
class Player {
public:
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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	float inputFloat3[3] = { 0,0,0 };
};
