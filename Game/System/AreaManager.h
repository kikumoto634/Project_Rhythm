#pragma once
#include <sstream>
#include <string>

#include "../3D/Plane/Planes.h"
#include "../3D/Wall/Walls.h"
#include "../3D/Wall/IndestructibleWall.h"

#include "GameManager.h"

class AreaManager
{
private:
	static const int DIV_NUM = 31;
	static const float DIV_NUM_FLOAT;
	static const int DIV_NUM_HALF = 15;
	static const float DIV_NUM_HALF_FLOAT;
	static const float Block_Size;

private:
	//領域
struct Area{
	int X;
	int Y;

	int Width;
	int Height;
};

//部屋
struct Room{
	int X;
	int Y;

	int Width;
	int Height;
};
public:
	void RandamAreaInitialize();
	void CSVAreaInitialize(std::string name);

	void RandamAreaUpdate(Camera* camera, Vector3 PlayerPos);
	void CSVAreaUpdate(Camera* camera, Vector3 PlayerPos);

	void BeatEndUpdate(GameManager* gameManager);

	void RandamAreaDraw();
	void CSVAreaDraw();

	void ParticleDraw();

	void RandamAreaFinalize();
	void CSVAreaFinalize();

	//ランダム用
	Vector3 GetExitPosition()	{return exitPosition;}
	Vector3 GetPlayerPosition()	{return PlayerPopPosition;}
	Vector3 GetObjectPopPosition();
	
	//CSV用
	Vector3 GetCSVObjectPopPosition(int index);
	bool GetCSVObjectPopActive(int index, bool IsFlag = true);
	int GetCSVObjectSize()	{return (int)ObjectPos.size();}

private:
	//地面
	void RandamAreaPlaneInitialize();
	void CSVAreaPlaneInitialize();
	void PlaneUpdate();
	void PlaneBeatEndUpdate();
	void PlaneDraw();
	void PlaneFinalize();

	//壁
	void RandamAreaWallsInitialize();
	void CVSAreaWallsInitialize();
	void WallUpdate();
	void WallBeatEndUpdate();
	void WallDraw();
	void WallParticleDraw();
	void WallFinalize();

	//破壊不可
	void RandamAreaIndestructibleWallInitialize();
	void CSVAreaIndestructibleWallInitialize();
	void IndestructibleWallUpdate();
	void IndestructibleWallDraw();
	void IndestructibleWallFinalize();

	//ダンジョン生成
	void CreateMap();
	Room DevideRoom(Area area, bool hr = false);
	Room CreateRoom(Area area);
	void ConnectRoom(Room parent, Room childRoom, int divline, bool hr);

	//CSV読み込み
	void CSVMapDataLoad(std::string fullPath);

	//座標
	void ObjectRandomPop();
	

private:
	//借りもの
	Camera* camera = nullptr;
	GameManager* gameManager = nullptr;
	Vector3 PlayerPos={};

	//Plane
	ObjModelManager* PlaneModel = nullptr;
	Planes* plane[DIV_NUM][DIV_NUM] = {nullptr};
	bool IsComboColorChange = false;

	//Wall
	ObjModelManager* WallModel = nullptr;
	ObjModelManager* WallColliderModel = nullptr;
	bool IsAlive = false;
	char WallMap[DIV_NUM][DIV_NUM] = {};
	Walls* Wall[DIV_NUM][DIV_NUM] = {nullptr};

	//破壊不可能壁
	ObjModelManager* IndestructibleWallModel = nullptr;
	ObjModelManager* IndestructibleWallColliderModel = nullptr;
	IndestructibleWall* IndestructibleWalls[DIV_NUM][DIV_NUM] = {nullptr};

	//部屋
	std::vector<Room> rooms;

	//出口
	Vector3 exitPosition = {0,-5,0};

	//プレイヤー
	Vector3 PlayerPopPosition = {0,-3,0};

	//生成オブジェクト
	Vector3 ObjectPopPosition = {0,0,0};

	//CSVコマンド
	std::stringstream csvCommands;
	int CSVMap[DIV_NUM][DIV_NUM] = {0};
	std::vector<Vector3> ObjectPos;
	std::vector<bool> ObjectPopActive;

};

