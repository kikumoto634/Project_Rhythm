#include "PlayerWeapon.h"
#include "../../Collision/CollisionSystem/CollisionManager.h"
#include "../../Collision/CollisionSystem/CollisionAttribute.h"

using namespace DirectX;

PlayerWeapon::~PlayerWeapon()
{
	//Finalize();
}

void PlayerWeapon::Initialize(std::string filePath, bool IsSmoothing)
{
	BaseObjObject::Initialize(filePath, IsSmoothing);

	object->SetColor({1.0f,0.0f,0.0f,1.0f});

	//コライダーの追加
	float radius = 0.6f;
	//半径文だけ足元から浮いた座標を球の中心にする
	SetCollider(new SphereCollider(XMVECTOR{0,radius,0,0}, radius));

	//当たり判定属性
	collider->SetAttribute(COLLISION_ATTR_ALLIES);

	//球コライダー取得
	sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);
}

void PlayerWeapon::Update(Camera *camera)
{
	if(!IsAppear) return;
	this->camera = camera;
	
	//生存フレーム
	if(aliveCurrentFrame >= AliveFrame) {
		aliveCurrentFrame = 0;

		world.translation = Vector3(0,-10,0);
		BaseObjObject::Update(this->camera);

		IsAppear = false;
		return;
	}
	aliveCurrentFrame++;

	//コライダー更新
	collider->Update();

	//ベース更新
	BaseObjObject::Update(this->camera);
}

void PlayerWeapon::Draw()
{
#ifdef _DEBUG
	if(!IsAppear) return;

	BaseObjObject::Draw();
#endif // _DEBUG
}

void PlayerWeapon::Finalize()
{
	BaseObjObject::Finalize();
}

void PlayerWeapon::OnCollision(const CollisionInfo &info)
{
	if(info.collider->GetAttribute() == COLLISION_ATTR_ENEMYS){
		camera->ShakeStart();
	}
}

void PlayerWeapon::Attack()
{
	IsAppear = true;
	world.translation = Vector3(0,1,2.5);
}
