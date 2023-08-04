#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<Input.h>
#include"PlayerBullet.h"
#include"list"
#include"ImGuiManager.h"
#include"RailCamera.h"
class Player {
public:
	~Player();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="model"></param>
	/// <param name="textureHandle"></param>
	void Initialize(Model* model, uint32_t textureHandle, Vector3 playerPosition);
	
	void Update();
	
	void Translate();

	void Rotate();

	void Attack();

	void OnCollition();

	void SetParent(const WorldTransform* parent);

	Vector3 GetWorldPosition();
	WorldTransform GetWorldTransform() { return worldTransform_; }
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection viewProjection);

	std::list<PlayerBullet*>bullets_;

private:
	PlayerBullet* bullet_ = nullptr;
	RailCamera* railCamera_ = nullptr;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	int32_t FireTimer = 1;
	float inputWorld3[3] = {0, 0, 0};
	float inputtranslate3[3] = {0, 0, 0};
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 18;
};
