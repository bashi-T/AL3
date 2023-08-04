#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"ALVector.h"
#include<Input.h>
#include"ImGuiManager.h"

class RailCamera {
public:
	void Initialize(Vector3 translate, Vector3 radian);

	void Update();

	void Translate();

	void Rotate();


	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	// const std::list<WorldTransform*>& GetWorldTransform() const { return WorldTransform_; }
	//std::list<WorldTransform*> WorldTransform_;

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
};
