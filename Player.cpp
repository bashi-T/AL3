#include<assert.h>
#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {

	assert(model);
	model = Model::Create();
	textureHandle = TextureManager::Load("cube.jpg");
	worldTransform_.Initialize();
};

void Player::Update() {
	worldTransform_.TransferMatrix();
};

void Player::Draw(ViewProjection viewProjection_, uint32_t textureHandle) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle);
};