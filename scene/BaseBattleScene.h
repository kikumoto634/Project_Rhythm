#pragma once
#include "BaseScene.h"

#include "../Game/3D/SampleFbxObject/SampleFbxObject.h"
#include "../Game/3D/SampleObjObject/SampleObjObject.h"
#include "../Engine/3D/TouchableObject.h"

#include "../Game/3D/Player/Player.h"
#include "../Game/3D/Exit/Exit.h"

#include "../Game/2D/JudgeLocation/JudgeLocation.h"
#include "../Game/2D/Notes/Notes.h"

#include "../Game/Collision/CollisionSystem/CollisionPrimitive.h"
#include "../Game/Collision/CollisionSystem/CollisionManager.h"

#include "../Game/System/RhythmManager.h"
#include "../Game/System/GameManager.h"
#include "../Game/System/AreaManager.h"

class BaseBattleScene : public BaseScene
{
protected:
	//シーン遷移
	const float FadeSecond = 1.f;

	//ノーツ数
	const int notesNum= 4;

public:
	
	//コンストラクタ
	BaseBattleScene(DirectXCommon* dxCommon, Window* window, int saveHP = 5, int floorVaule = 1);

	~BaseBattleScene();

	/// <summary>
	/// 起動時
	/// </summary>
	void Application() override;

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

private:
	//初期化
	void CommonInitialize();
	void Object3DInitialize();
	void Object2DInitialize();

	//更新
	void InputUpdate();
	void Object3DUpdate();
	void Object2DUpdate();
	void CommonUpdate();

	//リズム関連
	void RhythmMeasure();
	void RhythmJudgeUpdate();
	void BeatEndUpdate();

	//描画
	void Object3DDraw();
	void ParticleDraw();
	void UIDraw();

	//後処理
	void ObjectFinaize();
	void CommonFinalize();

protected:

	//シーン遷移
	virtual void SceneGameEnd();
	virtual void NextSceneChange() = 0;
	virtual void SceneChange();

	//初期化
	virtual void AddCommonInitialize() = 0;
	virtual void AddObject3DInitialize() = 0;
	virtual void AddObject2DInitialize() = 0;

	//更新
	virtual void AddCommonUpdate() = 0;
	virtual void AddObject3DUpdate() = 0;
	virtual void AddObject2DUpdate() = 0;
	virtual void AddBeatEndUpdate() = 0;

	//描画
	virtual void AddObject3DDraw() = 0;
	virtual void AddParticleDraw() = 0;
	virtual void AddUIDraw() = 0;

	//後処理
	virtual void AddObjectFinalize() = 0;
	virtual void AddCommonFinalize() = 0;


private:
	void VectorObjIni();

protected:
	//共通
	//衝突マネージャー
	CollisionManager* collisionManager = nullptr;

	//持ち越し
	//セーブ体力
	int saveHP = 0;
	//階層
	int floorValue = 1;

	//player
	std::unique_ptr<Player> player;
	//リズムカウント
	std::unique_ptr<RhythmManager> rhythmManager;
	//ゲームマネージャー
	std::unique_ptr<GameManager> gameManager;
	//リズム入力
	bool IsRhythmInput = false;
	//出口
	std::unique_ptr<Exit> exit;
	//エリアマネージャー
	std::unique_ptr<AreaManager> areaManager;

#ifdef _DEBUG
	//カメラ移動、回転変更フラグ
	bool IsCameraMovementChange = true;
#endif // _DEBUG

	//シーン遷移
	std::unique_ptr<BaseSprites> fade;
	DirectX::XMFLOAT4 fadeColor = {0,0,0,1};
	Vector2 fadeInSize = {};
	float fadeCurrentFrame = 0;
	//Prev
	bool IsPrevSceneChange = true;
	//Next
	bool IsNextSceneChange = false;

	//GameOver
	bool IsGameEnd = false;

	//BGM再生フラグ
	bool IsBGMStart = true;

	//リズム目視確認用SP
	std::unique_ptr<JudgeLocation> judgeLoca;

	std::vector<std::unique_ptr<Notes>> Lnotes;
	Notes* LNotes_InputTarget;
	bool IsNoteInput = false;
};