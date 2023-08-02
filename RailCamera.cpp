#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translate, Vector3 radian) {
	worldTransform_.translation_ = translate;
	worldTransform_.rotation_ = radian;
	input_ = Input::GetInstance();
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	Vector3 move = {0, 0, 0};
	Vector3 rotate = {0, 0, 0};
	const float kCameraSpeed = 0.4f;

	if (input_->PushKey(DIK_H))
	{
		move.x += kCameraSpeed;
	}
	if (input_->PushKey(DIK_F))
	{
		move.x -= kCameraSpeed;
	}
	if (input_->PushKey(DIK_T))
	{
		move.y += kCameraSpeed;
	}
	if (input_->PushKey(DIK_B))
	{
		move.y -= kCameraSpeed;
	}
	if (input_->PushKey(DIK_Y))
	{
		move.z += kCameraSpeed;
	}
	if (input_->PushKey(DIK_V))
	{
		move.z -= kCameraSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_D))
	{
		rotate.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_A))
	{
		rotate.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_W))
	{
		rotate.x += kRotSpeed;
	}
	if (input_->PushKey(DIK_X))
	{
		rotate.x -= kRotSpeed;
	}
	if (input_->PushKey(DIK_E))
	{
		rotate.z += kRotSpeed;
	}
	if (input_->PushKey(DIK_Z))
	{
		rotate.z -= kRotSpeed;
	}

	worldTransform_.rotation_.x += rotate.x;
	worldTransform_.rotation_.y += rotate.y;
	worldTransform_.rotation_.z += rotate.z;
	
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_);

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	float inputTranslationFloat3[3] = 
	{
	    worldTransform_.translation_.x,
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z
	};

	float inputRotationFloat3[3] =
	{
	    worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
		worldTransform_.rotation_.z
	};

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("translation", inputTranslationFloat3, 0.0f, 1.0f);
	ImGui::SliderFloat3("rotation", inputRotationFloat3, 0.0f, 1.0f);
	ImGui::End();
}
