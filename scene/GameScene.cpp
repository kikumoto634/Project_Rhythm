#include "GameScene.h"

#include "TitleScene.h"
#include "SceneManager.h"

using namespace std;

GameScene::GameScene(DirectXCommon *dxCommon, Window *window, int saveHP)
	:BaseBattleScene(
		dxCommon,
		window)
{
}

void GameScene::NextSceneChange()
{
	sceneManager->SetNextScene(new GameScene(dxCommon,window));
}

void GameScene::AreaManagerInitialize()
{
	//ダンジョン
	//BaseBattleScene::AreaManagerInitialize();
	//areaManager->RandamAreaInitialize();
	areaManager->CSVAreaInitialize("Tutorial");
}

void GameScene::AddCommonInitialize()
{
}

void GameScene::AddObject3DInitialize()
{
	slimePopNumMax = 2;
	coinPopNumMax = 2;
	ActorCreateInitialize();
}

void GameScene::AddObject2DInitialize()
{
}

void GameScene::AddCommonUpdate()
{
}

void GameScene::AddObject3DUpdate()
{
	for(auto it = slime.begin(); it != slime.end(); it++){
		if((*it)->GetIsDeadAudio()){
			gameManager->AudioPlay(2, 0.5f);
			for(auto it2 = coin.begin(); it2!= coin.end(); it2++){
				if((*it2)->PopPossible()){
					(*it2)->Pop({(*it)->GetDeadParticlepos().x, -5, (*it)->GetDeadParticlepos().z});
					break;
				}
			}
		}
		(*it)->Update(camera,player->GetPosition());
	}

	for(auto it = coin.begin(); it != coin.end(); it++){
		if((*it)->GetCoin()){
			gameManager->CoinIncrement();
			gameManager->AudioPlay(7,0.5f);
		}
		(*it)->Update(this->camera);
	}
}

void GameScene::AddObject2DUpdate()
{
}

void GameScene::AddBeatEndUpdate()
{
	int index = 0;
	for(auto it = slime.begin(); it != slime.end(); it++){
		(*it)->IsBeatEndOn();
		if(!(*it)->GetIsNotApp()){
			Vector3 lpos;
			//lpos = areaManager->GetObjectPopPosition();

			if(areaManager->GetCSVObjectPopActive(index,false)) {
				lpos = areaManager->GetCSVObjectPopPosition(index);
				(*it)->Pop({lpos.x, -3.5f,lpos.z});
			}
			index++;
		}
	}

	for(auto it = coin.begin(); it != coin.end(); it++){
		if((*it)->GetIsAlive()){
			(*it)->IsBeatEndOn();
		}
	}
}

void GameScene::AddObject3DDraw()
{
	for(auto it = slime.begin(); it != slime.end(); it++){
		(*it)->Draw();
	}
	for(auto it = coin.begin(); it != coin.end(); it++){
		(*it)->Draw();
	}
}

void GameScene::AddParticleDraw()
{
	for(auto it = slime.begin(); it != slime.end(); it++){
		(*it)->ParticleDraw();
	}
}

void GameScene::AddUIDraw()
{
}

void GameScene::AddObjectFinalize()
{

	for(auto it = slime.begin(); it != slime.end(); it++){
		(*it)->Finalize();
	}

	for(auto it = coin.begin(); it != coin.end(); it++){
		(*it)->Finalize();
	}
}

void GameScene::AddCommonFinalize()
{
}


void GameScene::ActorCreateInitialize()
{
	for(int i = 0; i < slimePopNumMax; i++){
		unique_ptr<BlueSlime> newObj = make_unique<BlueSlime>();
		newObj->Initialize("slime");
		slime.push_back(move(newObj));
	}

	for(int i = 0; i < coinPopNumMax; i++){
		unique_ptr<Coins> newObj = make_unique<Coins>();
		newObj->Initialize("Coins");
		coin.push_back(move(newObj));
	}
}
