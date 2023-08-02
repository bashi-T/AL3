#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete modelSkydome_;
	delete railCamera_;
}

void GameScene::Initialize()
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	viewProjection_.Initialize();
	modelSkydome_ = Model::CreateFromOBJ("world", true);

	player_ = new Player();
	Vector3 playerPosition(0, 0, 20);
	player_->Initialize(model_, textureHandle_, playerPosition);
	
	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	enemy_->Initialise(model_);

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);

	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, -30}, {0, 0, 0});
	player_->SetParent(&railCamera_->GetWorldTransform());

	debugCamera_ = new DebugCamera(640, 360);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update()
{
	player_->Update();
	enemy_->Update();
	skydome_->Update();
	//debugCamera_->Update();

	railCamera_->Update();
	viewProjection_.matView = railCamera_->
		GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->
		GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();
	CheckAllCollitions();
//#ifdef _DEBUG
//	if (input_->TriggerKey(DIK_S))
//	{
//		isDebugCameraActive_ = true;
//	}
//#endif

	//if (isDebugCameraActive_) {
	//	debugCamera_->Update();
	//	viewProjection_.matView = debugCamera_->
	// GetViewProjection().matView;
	//	viewProjection_.matProjection = debugCamera_->
	// GetViewProjection().matProjection;
	//	viewProjection_.TransferMatrix();
	//}
	//else 
	//{
	//	viewProjection_.UpdateMatrix();
	//}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollitions()
{
	Vector3 posA, posB;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
#pragma region
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets)
	{
		posB = bullet->GetWorldPosition();
		Vector3 distance = Subtract(posA, posB);
		if ((distance.x * distance.x) + (distance.y * distance.y) +
			(distance.z * distance.z) <= 4)
		{
			player_->OnCollition();
			bullet->OnCollition();
		}
	}
#pragma endregion

#pragma region
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets)
	{
		posB = bullet->GetWorldPosition();
		Vector3 distance = Subtract(posA, posB);
		if ((distance.x * distance.x) + (distance.y * distance.y) +
			(distance.z * distance.z) <= 4)
		{
			player_->OnCollition();
			bullet->OnCollition();
		}
	}
#pragma endregion

#pragma region
	for (PlayerBullet* PlayerBullet : playerBullets) {
		for (EnemyBullet* EnemyBullet : enemyBullets) {
			posA = PlayerBullet->GetWorldPosition();
			posB = EnemyBullet->GetWorldPosition();
			Vector3 distance = Subtract(posA, posB);
			if ((distance.x * distance.x) + (distance.y * distance.y) +
				(distance.z * distance.z) <= 4)
			{
				PlayerBullet->OnCollition();
				EnemyBullet->OnCollition();
			}
		}
	}
#pragma endregion
}
