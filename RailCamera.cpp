#include "RailCamera.h"

void RailCamera::Initialize(Vector3 translate, Vector3 radian) {
	worldTransform_.translation_ = translate;
	worldTransform_.rotation_ = radian;
	viewProjection_.Initialize();
}

void RailCamera::Update()
{
	Vector3 move = {0, 0, 0};
	Vector3 rotate = {0, 0, 0};
	const float kCameraSpeed = 0.4f;

	if (input_->PushKey(DIK_H)) {
		move.x += kCameraSpeed;
	}
	if (input_->PushKey(DIK_F)) {
		move.x -= kCameraSpeed;
	}
	if (input_->PushKey(DIK_T)) {
		move.y += kCameraSpeed;
	}
	if (input_->PushKey(DIK_B)) {
		move.y -= kCameraSpeed;
	}
	if (input_->PushKey(DIK_Y)) {
		move.z += kCameraSpeed;
	}
	if (input_->PushKey(DIK_V)) {
		move.z -= kCameraSpeed;
	}
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

		const float kCameraRotate = 0.1f;

	if (input_->PushKey(DIK_D)) {
		rotate.x += kCameraRotate;
	}
	if (input_->PushKey(DIK_A)) {
		rotate.x -= kCameraRotate;
	}
	if (input_->PushKey(DIK_W)) {
		rotate.y += kCameraRotate;
	}
	if (input_->PushKey(DIK_X)) {
		rotate.y -= kCameraRotate;
	}
	if (input_->PushKey(DIK_E)) {
		rotate.z += kCameraRotate;
	}
	if (input_->PushKey(DIK_Z)) {
		rotate.z -= kCameraRotate;
	}
	worldTransform_.rotation_.x += rotate.x;
	worldTransform_.rotation_.y += rotate.y;
	worldTransform_.rotation_.z += rotate.z;
	
	worldTransform_.matWorld_=
}
