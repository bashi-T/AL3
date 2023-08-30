#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"AxisIndicator.h"
#include<fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	//delete enemy_;
	delete modelSkydome_;
	delete railCamera_;
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
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
	TextureManager::Load("Sight.png");
	player_ = new Player();
	Vector3 playerPosition(0, 0, 30);
	
	LoadEnemyPopData();
	
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);

	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, -60}, {0, 0, 0});
	player_->SetParent(&railCamera_->GetWorldTransform());
	player_->Initialize(model_, textureHandle_, playerPosition);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update()
{
	if (SceneNumber == 0)
	{

	}
	if (SceneNumber == 0 && input_->PushKey(DIK_SPACE))
	{
		SceneNumber = 1;
	}
	if (SceneNumber==1)
	{
		railCamera_->Update();

		viewProjection_.matView = railCamera_->GetViewProjection().matView;

		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();

		player_->Update(viewProjection_);

		UpdateEnemyPopCommands();

		enemys_.remove_if([](Enemy* enemy) {
			if (enemy->IsDead()) {
				delete enemy;
				return true;
			}
			return false;
		});
		enemyBullets_.remove_if([](EnemyBullet* bullet) {
			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}
			return false;
		});
		for (Enemy* enemy : enemys_) {
			enemy->Update();
		}
		for (EnemyBullet* bullet : enemyBullets_) {
			bullet->Update();
		}

		skydome_->Update();

		CheckAllCollitions();
	}

	//debugCamera_->Update();
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
	for (Enemy*enemy:enemys_) {
		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	player_->DrawUI();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollitions()
{
	Vector3 posA, posB;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<Enemy*>& enemys = GetEnemys();
	const std::list<EnemyBullet*>& enemyBullets = GetBullets();
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
	for (PlayerBullet* PlayerBullet : playerBullets)
	{
		for (Enemy* Enemy : enemys)
		{
			posA = PlayerBullet->GetWorldPosition();
			posB = Enemy->GetWorldPosition();
			Vector3 distance = Subtract(posA, posB);
			if ((distance.x * distance.x) + (distance.y * distance.y) +
				(distance.z * distance.z) <= 4)
			{
				PlayerBullet->OnCollition();
				Enemy->OnCollition();
			}
		}
	}
#pragma endregion

#pragma region
	for (PlayerBullet* PlayerBullet : playerBullets)
	{
		for (EnemyBullet* EnemyBullet : enemyBullets)
		{
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

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet)
{
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::Encount(Vector3 translate)
{
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialise(model_, translate);
	enemys_.push_back(newEnemy);
	newEnemy->SetPlayer(player_);
	newEnemy->SetGameScene(this);
}

void GameScene::LoadEnemyPopData()
{
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());
	enemyPopCommands << file.rdbuf();
	file.close();
}

void GameScene::UpdateEnemyPopCommands()
{
	if (waitFlag)
	{
		WaitTimer--;
		if (WaitTimer <= 0)
		{
			waitFlag = false;
		}
		return;
	}
	std::string line;
	while (getline(enemyPopCommands, line))
	{
		std::istringstream line_stream(line);
		std::string word;
		getline(line_stream, word, ',');
		if (word.find("//") == 0)
		{
			continue;
		}
		if (word.find("POP") == 0)
		{
			getline(line_stream, word, '.');
			float x = (float)std::atof(word.c_str());
			getline(line_stream, word, '.');
			float y = (float)std::atof(word.c_str());
			getline(line_stream, word, '.');
			float z = (float)std::atof(word.c_str());
			Encount(Vector3(x, y, z));
		} else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');
			int32_t waitTime = atoi(word.c_str());
			waitFlag = true;
			WaitTimer = waitTime;
			break;
		}
	}
}
