#include<Player.h>
#include<assert.h>

void Player::Initialize(Model* model, uint32_t textureHandle){
	assert(model);
	textureHandle = TextureManager::Load("cube.jpg");
	model = Model::Create();
	worldTransform_.Initialize();
};

void Player::Update(){
	worldTransform_.TransferMatrix();
};

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
};