#pragma once
#include "BaseBattleScene.h"

#include "../Game/3D/Enemy/BlueSlime.h"
#include "../Game/3D/Coins/Coins.h"

class GameScene : public BaseBattleScene
{
public:
	GameScene(DirectXCommon* dxCommon, Window* window, int saveHP = 5);

private:
//シーン遷移
	void NextSceneChange() override;

	//初期化
	void AreaManagerInitialize() override;
	void AddCommonInitialize() override;
	void AddObject3DInitialize() override;
	void AddObject2DInitialize() override;

	//更新
	void AddCommonUpdate() override;
	void AddObject3DUpdate() override;
	void AddObject2DUpdate() override;
	void AddBeatEndUpdate() override;

	//描画
	void AddObject3DDraw() override;
	void AddParticleDraw() override;
	void AddUIDraw() override;

	//後処理
	void AddObjectFinalize() override;
	void AddCommonFinalize() override;

private:
	std::unique_ptr<BlueSlime> slime;
	std::unique_ptr<Coins> coin;
};

