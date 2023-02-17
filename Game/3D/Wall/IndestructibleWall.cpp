#include "IndestructibleWall.h"
#include "../../Collision/SphereCollider.h"
#include "../../Collision/CollisionSystem/CollisionManager.h"

using namespace DirectX;

IndestructibleWall::~IndestructibleWall()
{
	//Finalize();
}

void IndestructibleWall::Initialize(ObjModelManager* model)
{
	BaseObjObject::Initialize(model);
}

void IndestructibleWall::Update(Camera *camera)
{
	this->camera = camera;

	if(!IsAlive) return;
	Vector3 pos = PlayerPos - world.translation;
	distance = pos.length();

	if(-13 <= distance && distance <= 13)		{
		IsHide = true;

		if(!IsCollision){
			//�R���C�_�[�ǉ�
			MeshCollider* collider = new MeshCollider;
			SetCollider(collider);
			//�����Z�b�g
			collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
			collider->ConstructTriangles(model);
			IsCollision = true;
		}
	}
	else if(-13 > distance || distance > 13){
		IsHide = false;

		if(IsCollision){
			if(collider){
				//�R���W�����}�l�[�W���[����o�^����������
				CollisionManager::GetInstance()->RemoveCollider(collider);
			}
			IsCollision = false;
		}
	}
	

	if(!IsHide) return;
	BaseObjObject::Update(this->camera);
}

void IndestructibleWall::Draw()
{
	if(!IsAlive) return;
	if(!IsHide) return;
	BaseObjObject::Draw();
}


void IndestructibleWall::Finalize()
{
	BaseObjObject::Finalize();
}

void IndestructibleWall::OnCollision(const CollisionInfo &info)
{
	if(!IsAlive) return;
	if(!IsHide) return;
}