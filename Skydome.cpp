#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 0, 0};
	//worldTransform_.scale_ = {150, 150, 150};
}

void Skydome::Update()
{ 
	worldTransform_.UpdateMatrix();
}

void Skydome::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
