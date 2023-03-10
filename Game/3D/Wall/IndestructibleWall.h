#pragma once
#include "../BaseObjObject.h"
#include "../../Collision/MeshCollider.h"
#include "../../Collision/CollisionSystem/CollisionAttribute.h"

class IndestructibleWall : public BaseObjObject
{
//死亡後のリセット時間
	const int DigAppearanceFrame = 50;
public:
	~IndestructibleWall();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns></returns>
	void Initialize(ObjModelManager* model, ObjModelManager* collider);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(Camera* camera) override;

	/// <summary>
	/// 3D描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// 後処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	void OnCollision(const CollisionInfo& info) override;

	void ColliderRemove();

	inline void IsNotAlive()	{IsAlive = false;}

	//Getter
	inline bool GetIsAlive()	{return IsAlive;}

	//Setter
	inline void SetPlayerPos(Vector3 pos)	{PlayerPos = pos;}

private:
	Vector3 PlayerPos;
	float distance = 0;

	//エリアで使用しない
	bool IsAlive = true;
	//距離に応じた非表示
	bool IsHide = false;

	//メッシュコライダー用モデル
	ObjModelManager* colliderModel = nullptr;
	bool IsCollision = false;
};

