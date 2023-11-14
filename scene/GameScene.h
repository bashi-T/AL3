#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include"Player.h"
#include"Enemy.h"
#include"DebugCamera.h"
#include"Skydome.h"
#include"RailCamera.h"
#include"sstream"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(/*ViewProjection*/);

	void CheckAllCollitions();

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void Encount(Vector3 translate);

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	std::list<EnemyBullet*> enemyBullets_;
	const std::list<EnemyBullet*> GetBullets() const { return enemyBullets_; }
	std::list<Enemy*> enemys_;
	const std::list<Enemy*> GetEnemys() const { return enemys_; }
	std::stringstream enemyPopCommands;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	Model* model_ = nullptr;
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	//Enemy* enemy_ = nullptr;
	EnemyBullet* enemyBullet_ = nullptr;
	PlayerBullet* playerBullet_ = nullptr;
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	RailCamera* railCamera_ = nullptr;
	int32_t EncountTimer_ = 1;
	bool waitFlag = false;
	int32_t WaitTimer = 1;
};
