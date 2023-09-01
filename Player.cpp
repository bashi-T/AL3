#include"Player.h"

Player::~Player()
{
	for (PlayerBullet* bullet : bullets_)
	{
	   delete bullet;
	}
	delete sprite2DReticle_;
}
void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 playerPosition) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	ReticleModel_ = model;
	ReticleTextureHandle_ = TextureManager::Load("Sight.png");
	
	uint32_t textureReticle = TextureManager::Load("Sight.png");
	sprite2DReticle_ = Sprite::Create(textureReticle,
		{720, 360}, {1.0f,1.0f,1.0f,1.0f}, {0.5f, 0.5f});

	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransformDefault_.Initialize();
	worldTransform_.translation_ = playerPosition;
	worldTransform_.matWorld_.m[3][0] = playerPosition.x;
	worldTransform_.matWorld_.m[3][1] = playerPosition.y;
	worldTransform_.matWorld_.m[3][2] = playerPosition.z;
	worldTransform3Dreticle_.Initialize();
};

void Player::Update(const ViewProjection viewProjection) {
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Translate();

	worldTransform_.scale_.x = worldTransformDefault_.scale_.x + NegaTimer / 360.0f;
	worldTransform_.scale_.y = worldTransformDefault_.scale_.y + NegaTimer / 360.0f;
	worldTransform_.scale_.z = worldTransformDefault_.scale_.z + NegaTimer / 360.0f;

	worldTransform_.UpdateMatrix();
	worldTransform_.matWorld_.m[3][0] = max(worldTransform_.matWorld_.m[3][0], -kMoveLimitX);
	worldTransform_.matWorld_.m[3][0] = min(worldTransform_.matWorld_.m[3][0], +kMoveLimitX);
	worldTransform_.matWorld_.m[3][1] = max(worldTransform_.matWorld_.m[3][1], -kMoveLimitY);
	worldTransform_.matWorld_.m[3][1] = min(worldTransform_.matWorld_.m[3][1], +kMoveLimitY);

	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = {0, 0, 1.0f};
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	offset = Multiply(kDistancePlayerTo3DReticle, Normalize(offset));
	worldTransform3Dreticle_.translation_ = Transform(offset, worldTransform_.matWorld_);
	worldTransform3Dreticle_.UpdateMatrix();

	Vector3 positionReticle =
	{
	    worldTransform3Dreticle_.matWorld_.m[3][0],
		worldTransform3Dreticle_.matWorld_.m[3][1],
	    worldTransform3Dreticle_.matWorld_.m[3][2]
	};
	Matrix4x4 matViewport =
	    MakeViewportMatrix(offset.x, offset.y, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	Matrix4x4 matViewProjectionViewport =
	    Multiply(viewProjection.matView, viewProjection.matProjection);
	matViewProjectionViewport = Multiply(matViewProjectionViewport, matViewport);

	positionReticle = Transform(positionReticle, matViewProjectionViewport);

	Vector2 spritePosition = sprite2DReticle_->GetPosition();

	XINPUT_STATE joyState;
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	   spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 7.5f;
	   spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 7.5f;
	   sprite2DReticle_->SetPosition(spritePosition);
	}

	Matrix4x4 matVPV = Multiply(viewProjection.matView, viewProjection.matProjection);
	matVPV = Multiply(matVPV, matViewport);
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	Vector3 posNear =
	    Vector3(sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y, 0);
	Vector3 posFar =
	    Vector3(sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y, 1);
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 ReticleDirection = Subtract(posNear, posFar);
	ReticleDirection = Normalize(ReticleDirection);
	const float kDistanceTestObject = -80;
	worldTransform3Dreticle_.translation_ =
	    Add(posNear, Multiply(kDistanceTestObject, ReticleDirection));
	worldTransform3Dreticle_.UpdateMatrix();

	Attack();
	for (PlayerBullet* bullet : bullets_) {
	   bullet->Update();
	}
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
	   NegaState = 1;
	}
}

void Player::Translate()
{
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.4f;

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
	   move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
	   move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
}

void Player::Rotate()
{
	const float kRotSpeed = 0.02f;
	if (input_->PushKey(DIK_Q))
	{
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_R))
	{
		worldTransform_.rotation_.y += kRotSpeed;
	}
}

void Player::Attack()
{
	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState))
	{
		return;
	}
	if (joyState.Gamepad.wButtons&XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		FireTimer--;
		if (FireTimer == 0)
		{
			FireTimer = 10;
			const float kBulletSpeedZ = 1.0f;
			Vector3 velocity(0, 0, kBulletSpeedZ);
			velocity.x =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][0];
			velocity.y =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][1];
			velocity.z =
			    Subtract(worldTransform3Dreticle_.matWorld_, worldTransform_.matWorld_).m[3][2];
			velocity = Multiply(kBulletSpeedZ, Normalize(velocity));
			PlayerBullet* newBullet = new PlayerBullet();
			newBullet->Initialise(
				model_,
				worldTransform_.matWorld_,
				velocity);
			bullets_.push_back(newBullet);
		}
	} else {
		FireTimer = 1;
	}
}

void Player::OnCollition()
{
	Life--;
	if (Life == 0)
	{
		isDead_ = true;
	}
}

void Player::SetParent(const WorldTransform* parent)
{
	worldTransform_.parent_ = parent; }

void Player::DrawUI()
{
	sprite2DReticle_->Draw();
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
};

void Player::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (PlayerBullet* bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
};