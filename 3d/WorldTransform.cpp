#include "WorldTransform.h"

void WorldTransform::UpdateMatrix()
{
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	if (parent_) {
		matWorld_ =Multiply(parent_->matWorld_,matWorld_);
	}
	TransferMatrix();
}
