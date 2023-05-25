#include"Player.h"
#include<assert.h>
#include"ImGuiManager.h"

Player::~Player()
{
	for (PlayerBullet* bullet : bullets_) {
	   delete bullet;
	}
}
void Player::Initialize(Model* model, uint32_t textureHandle){
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
};

void Player::Update(){
	worldTransform_.UpdateMatrix();

	Vector3 move = { 0,0,0 };
	const float kCharacterSpeed = 0.4f;

	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}

	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_,
		worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	ImGui::Begin("position");
	inputFloat3[0] = worldTransform_.translation_.x;
	inputFloat3[1] = worldTransform_.translation_.y;
	inputFloat3[2] = worldTransform_.translation_.z;
	ImGui::InputFloat3("InputFloat3",inputFloat3);
	ImGui::End();

	const float kMoveLimitX = 33;
	const float kMoveLimitY = 18;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	Attack();
	for (PlayerBullet* bullet:bullets_) {
		bullet->Update();
	}
}

void Player::Rotate()
{
	const float kRotSpeed = 0.02f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}
void Player::Attack()
{
	if (input_->PushKey(DIK_SPACE)) {
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialise(model_, worldTransform_.translation_);
		bullets_.push_back(newBullet);
	}
}
;

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection_);
	}
};