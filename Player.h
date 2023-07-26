#pragma once
#include "ViewProjection.h"
#include "Model.h"
#include "WorldTransform.h"
#include<Input.h>
#include"PlayerBullet.h"
#include"list"
#include"ImGuiManager.h"

class Player {
public:
	~Player();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	void Initialize(Model* model, uint32_t textureHandle);
	
	void Update();
	
	void Rotate();

	void Attack();

	void OnCollition();

	Vector3 GetWorldPosition();

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

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
	int32_t FireTimer = 1;
	float inputFloat3[3] = {0, 0, 0};
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 18;
};
