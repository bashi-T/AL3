#include "enemy.h"
#include "Player.h"
#include"GameScene.h"
#include<math.h>

Enemy::~Enemy()
{
}

void Enemy::Initialise(Model* model,Vector3 translate)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("sand.png");
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = translate;
	worldTransform_.matWorld_.m[3][0] = translate.x;
	worldTransform_.matWorld_.m[3][1] = translate.y;
	worldTransform_.matWorld_.m[3][2] = translate.z;
	ResetApproach();
}

void Enemy::Update()
{
	
	const float kBulletSpeedZ = -0.5f;
	Vector3 velocity(0, 0, kBulletSpeedZ);

	//switch (phase_) {
	//case Phase::Approach:
	//default:
	//	Approach();
	//	break;
	//case Phase::Leave:
	//	Leave();
	//	break;
	//}

	MoveRand();
	worldTransform_.UpdateMatrix();
	//FireTimer--;
	//if (FireTimer == 0) {
	//	Fire();
	//	FireTimer = kFireInterval;
	//}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Approach()
{
	kEnemySpeedZ = -0.5f;
	worldTransform_.translation_.x += kEnemySpeedX;
	worldTransform_.translation_.y += kEnemySpeedY;
	worldTransform_.translation_.z += kEnemySpeedZ;
	if (worldTransform_.translation_.z < 20.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	kEnemySpeedZ = 0.5f;
	worldTransform_.translation_.x += kEnemySpeedX;
	worldTransform_.translation_.y += kEnemySpeedY;
	worldTransform_.translation_.z += kEnemySpeedZ;
	if (worldTransform_.translation_.z > 120.0f)
	{
		phase_ = Phase::Approach;
	}
}

void Enemy::Fire()
{
	assert(player_);
	assert(gameScene_);
	float kBulletSpeedX = -1.0f;
	float kBulletSpeedY = -1.0f;
	float kBulletSpeedZ = -1.0f;
	player_->GetWorldPosition();
	
	GetWorldPosition();
	Vector3 direction = Subtract( player_->GetWorldPosition(),GetWorldPosition());
	kBulletSpeedX = Normalize(direction).x;
	kBulletSpeedY = Normalize(direction).y;
	kBulletSpeedZ = Normalize(direction).z;
	Vector3 velocity(kBulletSpeedX, kBulletSpeedY, kBulletSpeedZ);

	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialise(model_, worldTransform_.translation_, velocity);
	gameScene_->enemyBullets_.push_back(newBullet);
}

void Enemy::ResetApproach()
{
	FireTimer = 10;
}

Vector3 Enemy::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollition() { isDead_ = true; }

void Enemy::MoveRand()
{
	worldTransform_.matWorld_.m[3][1] = 0.0f;
	if (stayTimer == 0)
	{
		stayTimer = 121;
	}
	if (stayTimer==121)
	{
		std::random_device rand;
		std::mt19937 mt(rand());
		std::uniform_int_distribution<> randX(-10,10);
		std::uniform_int_distribution<> randZ(0,20);
		distinationX = randX(mt);
		distinationZ = randZ(mt);
		stayTimer = 120;
	}
	if (IsDiscover==0)
	{
		distXYZ =
		{
			float(distinationX * mapsize),
			0.0f,
			float(distinationZ * mapsize)
		};
	};
	if (IsDiscover == 1)
	{
		distXYZ =
		{
		    player_->GetWorldTransform().matWorld_.m[3][0],
		    player_->GetWorldTransform().matWorld_.m[3][1],
		    player_->GetWorldTransform().matWorld_.m[3][2]
		};
	}
	if (IsDiscover == 2&&seekCount==300)
	{
		distXYZ =
		{
		    player_->GetWorldTransform().matWorld_.m[3][0],
		    player_->GetWorldTransform().matWorld_.m[3][1],
		    player_->GetWorldTransform().matWorld_.m[3][2]
		};
	}
	switch(IsDiscover)
	{
	case 0:
		if (worldTransform_.matWorld_.m[3][0] == distXYZ.x)
		{
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x >= enemySpeed)
		{
			worldTransform_.translation_.x -= enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x <= -enemySpeed)
		{
			worldTransform_.translation_.x += enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x < enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][0] - distXYZ.x;
			worldTransform_.translation_.x -= enemySpeed;
			enemySpeed = 0.25f;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x > -enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][0] - distXYZ.x;
			worldTransform_.translation_.x += enemySpeed;
			enemySpeed = 0.25f;
		}

		if (worldTransform_.matWorld_.m[3][2] == distXYZ.z)
		{
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z >= enemySpeed)
		{
			worldTransform_.translation_.z -= enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z <= -enemySpeed)
		{
			worldTransform_.translation_.z += enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z < enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][2] - distXYZ.z;
			worldTransform_.translation_.z -= enemySpeed;
			enemySpeed = 0.25f;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z > -enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][2] - distXYZ.z;
			worldTransform_.translation_.z += enemySpeed;
			enemySpeed = 0.25f;
		}
		if (worldTransform_.matWorld_.m[3][0] == distXYZ.x)
		{
			if (worldTransform_.matWorld_.m[3][2] == distXYZ.z)
			{
				stayTimer--;
			}
		}
		break;
	case 1:
		if (worldTransform_.matWorld_.m[3][0] == distXYZ.x)
		{
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x >= enemySpeed)
		{
			worldTransform_.translation_.x -= enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x <= -enemySpeed)
		{
			worldTransform_.translation_.x += enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x < enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][0] - distXYZ.x;
			worldTransform_.translation_.x -= enemySpeed;
			enemySpeed = 0.4f;
		} else if (worldTransform_.matWorld_.m[3][0] - distXYZ.x > -enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][0] - distXYZ.x;
			worldTransform_.translation_.x += enemySpeed;
			enemySpeed = 0.4f;
		}

		if (worldTransform_.matWorld_.m[3][2] == distXYZ.z)
		{
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z >= enemySpeed)
		{
			worldTransform_.translation_.z -= enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z <= -enemySpeed)
		{
			worldTransform_.translation_.z += enemySpeed;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z < enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][2] - distXYZ.z;
			worldTransform_.translation_.z -= enemySpeed;
			enemySpeed = 0.4f;
		} else if (worldTransform_.matWorld_.m[3][2] - distXYZ.z > -enemySpeed)
		{
			enemySpeed = worldTransform_.matWorld_.m[3][2] - distXYZ.z;
			worldTransform_.translation_.z += enemySpeed;
			enemySpeed = 0.4f;
		}
		break;
	case 2:
		seekCount--;
		if (seekCount == 0)
		{
			seekCount = 300;
			IsDiscover = 0;
		}
		break;
	}
}

void Enemy::SetIsDiscover() 
{
	IsDiscover++;
}
	
