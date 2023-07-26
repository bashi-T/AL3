#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"ALVector.h"
#include<Input.h>
#include"ImGuiManager.h"

class RailCamera {
public:
	void Initialize(Vector3 translate,Vector3 radian);

	void Update();

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Input* input_ = nullptr;
};
