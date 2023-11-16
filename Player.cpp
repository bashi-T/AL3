#include"Player.h"

Player::~Player()
{
	for (PlayerBullet* bullet : bullets_)
	{
	   delete bullet;
	}
	delete sprite2DReticle_;
}
void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 playerPosition)
{
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
	worldTransform_.translation_ = playerPosition;
	worldTransform_.matWorld_.m[3][0] = playerPosition.x;
	worldTransform_.matWorld_.m[3][1] = playerPosition.y;
	worldTransform_.matWorld_.m[3][2] = playerPosition.z;
	worldTransform3Dreticle_.Initialize();

};

void Player::Update(const ViewProjection viewProjection)
{
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Translate();

	Rotate();

	worldTransform_.UpdateMatrix();
	SetCollition();

	ImGui::Begin("player");
	inputWorld3[0] = worldTransform_.matWorld_.m[3][0];
	inputWorld3[1] = worldTransform_.matWorld_.m[3][1];
	inputWorld3[2] = worldTransform_.matWorld_.m[3][2];
	ImGui::InputFloat3("world", inputWorld3);
	inputtranslate3[0] = worldTransform_.translation_.x;
	inputtranslate3[1] = worldTransform_.translation_.y;
	inputtranslate3[2] = worldTransform_.translation_.z;
	ImGui::InputFloat3("translation", inputtranslate3);
	ImGui::End();

	//worldTransform_.matWorld_.m[3][0] =
	//    max(worldTransform_.matWorld_.m[3][0], -kMoveLimitX);
	//worldTransform_.matWorld_.m[3][0] =
	//    min(worldTransform_.matWorld_.m[3][0], +kMoveLimitX);
	//worldTransform_.matWorld_.m[3][1] =
	//	max(worldTransform_.matWorld_.m[3][1], -kMoveLimitY);
	//worldTransform_.matWorld_.m[3][1] =
	//	min(worldTransform_.matWorld_.m[3][1], +kMoveLimitY);

	//const float kDistancePlayerTo3DReticle = 50.0f;
	//Vector3 offset = {0, 0, 1.0f};
	//offset = TransformNormal(offset, worldTransform_.matWorld_);
	//offset = Multiply(kDistancePlayerTo3DReticle ,Normalize(offset));
	//worldTransform3Dreticle_.translation_ = Transform(offset, worldTransform_.matWorld_);
	//worldTransform3Dreticle_.UpdateMatrix();

	//Vector3 positionReticle =
 //   {
	//        worldTransform3Dreticle_.matWorld_.m[3][0],
	//        worldTransform3Dreticle_.matWorld_.m[3][1],
	//        worldTransform3Dreticle_.matWorld_.m[3][2]
	//};
	//Matrix4x4 matViewport = MakeViewportMatrix(
	//		offset.x,
	//		offset.y,
	//		WinApp::kWindowWidth,
	//		WinApp::kWindowHeight,
	//		0,
	//		1);

	//Matrix4x4 matViewProjectionViewport =
	//    Multiply(viewProjection.matView, viewProjection.matProjection);
	//matViewProjectionViewport =
	//	Multiply(matViewProjectionViewport, matViewport);

	//positionReticle = Transform(positionReticle, matViewProjectionViewport);
	//sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

	//POINT mousePosition;
	//GetCursorPos(&mousePosition);
	//HWND hwnd = WinApp::GetInstance()->GetHwnd();
	//ScreenToClient(hwnd, &spritePosition);
	//sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x,(float)mousePosition.y));
	//Vector2 spritePosition = sprite2DReticle_->GetPosition();

	//XINPUT_STATE joyState;
	//if (Input::GetInstance()->GetJoystickState(0, joyState)) {
	//   spritePosition.x += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * 10.0f;
	//   spritePosition.y -= (float)joyState.Gamepad.sThumbRY / SHRT_MAX * 10.0f;
	//   sprite2DReticle_->SetPosition(spritePosition);
	//}
	//Matrix4x4 matVPV = Multiply(viewProjection.matView, viewProjection.matProjection);
	//matVPV = Multiply(matVPV, matViewport);
	//Matrix4x4 matInverseVPV = Inverse(matVPV);

	//Vector3 posNear =
	//    Vector3(
	//		sprite2DReticle_->GetPosition().x,
	//		sprite2DReticle_->GetPosition().y,
	//		0);
	//Vector3 posFar =
	//    Vector3(
	//		sprite2DReticle_->GetPosition().x,
	//		sprite2DReticle_->GetPosition().y,
	//		1);
	//posNear = Transform(posNear, matInverseVPV);
	//posFar = Transform(posFar, matInverseVPV);

	//Vector3 ReticleDirection = Subtract(posNear, posFar);
	//ReticleDirection = Normalize(ReticleDirection);
	//const float kDistanceTestObject = -80;
	//worldTransform3Dreticle_.translation_ =
	//    Add(posNear, Multiply(kDistanceTestObject, ReticleDirection));
	//worldTransform3Dreticle_.UpdateMatrix();

	//ImGui::Begin("Player");
	//ImGui::Text("2DReticle:(%f,%f)",
	//	sprite2DReticle_->GetPosition().x,
	//	sprite2DReticle_->GetPosition().y);
	//ImGui::Text("Near:(%+.2f,%+.2f,%+.2f", posNear.x, posNear.y, posNear.z);
	//ImGui::Text("Far:(%+.2f,%+.2f,%+.2f", posFar.x, posFar.y, posFar.z);
	//ImGui::Text("3DReticle:(%+.2f,%+.2f,%+.2f",
	//	worldTransform3Dreticle_.translation_.x,
	//    worldTransform3Dreticle_.translation_.y,
	//	worldTransform3Dreticle_.translation_.z);
	//ImGui::End();   

	Attack();
	for (PlayerBullet* bullet : bullets_)
	{
	   bullet->Update();
	}
}

void Player::Translate()
{
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.6f;

	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState))
	{
	   move.x += (float)joyState.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
	   move.y += (float)joyState.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}

	//if (input_->PushKey(DIK_LEFT))
	//{
	//   move.x -= kCharacterSpeed;
	//}
	//if (input_->PushKey(DIK_RIGHT))
	//{
	//   move.x += kCharacterSpeed;
	//}
	//if (input_->PushKey(DIK_UP))
	//{
	//   move.y += kCharacterSpeed;
	//}
	//if (input_->PushKey(DIK_DOWN))
	//{
	//   move.y -= kCharacterSpeed;
	//}

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	//worldTransform_.translation_.z += move.z;
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

}

void Player::SetCollition()
{
		PlayerCorner[0] =//rightfront
	{ 
		worldTransform_.matWorld_.m[3][0] + 2.0f,
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2] + 2.0f
	};
	PlayerCorner[1] =//rightback
	{ 
		worldTransform_.matWorld_.m[3][0] + 2.0f,
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2] - 2.0f
	};
	PlayerCorner[2] =//leftfront
	{ 
		worldTransform_.matWorld_.m[3][0] - 2.0f,
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2] + 2.0f
	};
	PlayerCorner[3] =//leftback
	{ 
		worldTransform_.matWorld_.m[3][0] - 2.0f,
		worldTransform_.matWorld_.m[3][1],
		worldTransform_.matWorld_.m[3][2] - 2.0f
	};

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
	ReticleModel_->Draw(worldTransform3Dreticle_, viewProjection, ReticleTextureHandle_);
};