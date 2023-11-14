#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translate, Vector3 radian)
{
	worldTransform_.Initialize();
	worldTransform_.translation_ = translate;
	worldTransform_.matWorld_.m[3][0] = translate.x;
	worldTransform_.matWorld_.m[3][1] = translate.y;
	worldTransform_.matWorld_.m[3][2] = translate.z;
	worldTransform_.rotation_ = radian;
	input_ = Input::GetInstance();
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	Translate();
	Rotate();

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_,
		worldTransform_.rotation_,
		worldTransform_.translation_);

	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	float inputTranslationFloat3[3] =
	{
	    worldTransform_.matWorld_.m[3][0],
		worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]
	};

	float inputRotationFloat3[3] =
	{
	    worldTransform_.rotation_.x,
		worldTransform_.rotation_.y,
		worldTransform_.rotation_.z
	};

	ImGui::Begin("Camera");
	ImGui::SliderFloat3("world", inputTranslationFloat3, 0.0f, 1.0f);
	ImGui::SliderFloat3("rotation", inputRotationFloat3, 0.0f, 1.0f);
	ImGui::End();
}

void RailCamera::Translate()
{
	Vector3 move = {0, 0, 0};
	const float kCameraSpeed = 0.4f;

	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= kCameraSpeed;
	}
	if (input_->PushKey(DIK_RIGHT))
	{
		move.x += kCameraSpeed;
	}
	//if (input_->PushKey(DIK_T)) {
	//	move.y += kCameraSpeed;
	//}
	//if (input_->PushKey(DIK_B)) {
	//	move.y -= kCameraSpeed;
	//}
	if (input_->PushKey(DIK_UP))
	{
		move.z += kCameraSpeed;
	}
	if (input_->PushKey(DIK_DOWN))
	{
		move.z -= kCameraSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
}

void RailCamera::Rotate()
{
	Vector3 rotate = {0, 0, 0};

	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_R))
	{
		rotate.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_Q))
	{
		rotate.y -= kRotSpeed;
	}
	//if (input_->PushKey(DIK_W)) {
	//	rotate.x += kRotSpeed;
	//}
	//if (input_->PushKey(DIK_X)) {
	//	rotate.x -= kRotSpeed;
	//}
	if (input_->PushKey(DIK_E))
	{
		rotate.z += kRotSpeed;
	}
	if (input_->PushKey(DIK_W))
	{
		rotate.z -= kRotSpeed;
	}

	worldTransform_.rotation_.x += rotate.x;
	worldTransform_.rotation_.y += rotate.y;
	worldTransform_.rotation_.z += rotate.z;
}
