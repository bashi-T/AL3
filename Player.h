#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
