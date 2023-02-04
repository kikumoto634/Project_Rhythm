#include "Planes.h"

Planes::~Planes()
{
	//Finalize();
}

void Planes::Initialize(std::string filePath, bool IsSmmothing)
{
	BaseObjObject::Initialize(filePath, IsSmmothing);

	SetModel(model);

	//コライダー追加
	MeshCollider* collider = new MeshCollider;
	SetCollider(collider);
	//属性セット
	collider->SetAttribute(COLLISION_ATTR_LANDSHAPE);
	collider->ConstructTriangles(model);
}

void Planes::Update(Camera *camera)
{
	this->camera = camera;
	if(!IsAlive) return;
	Vector3 pos = PlayerPos - world.translation;
	distance = pos.length();

	if(-20 <= distance && distance <= 20)		{
		IsHide = true;
	}
	else if(-20 > distance || distance > 20)	IsHide = false;
	
	if(!IsHide) return;

	//拍終わり時
	if(IsBeatEnd){
		
		//プレイヤー接触時
		if(IsPlayerContact){
			//サイズ変更
			if(ScaleChange(ScaleMax, ScaleMin, scaleEndTime)){
				IsPlayerContact = false;
				IsBeatEnd = false;
			}
		}
	}

	BaseObjObject::Update(this->camera);
}

void Planes::Draw()
{
	if(!IsAlive) return;
	if(!IsHide) return;
	BaseObjObject::Draw();
}

void Planes::Finalize()
{
	BaseObjObject::Finalize();
}

void Planes::OnCollision(const CollisionInfo &info)
{
	if(!IsAlive) return;
	if(!IsHide) return;
	if(info.collider->GetAttribute() == COLLISION_ATTR_ALLIES){
		IsPlayerContact = true;
	}	
}

void Planes::PlaneColorChange(bool IsSwitch,  bool IsColorChange)
{
	if(!IsAlive) return;
	if(IsSwitch){
		if(IsColorChange){
			object->SetColor({0.0f, 0.8f, 0.0f,1.0f});
		}
		else if(!IsColorChange){
			object->SetColor({1.f,1.f,1.f,1.f});
		}
	}
	else if(!IsSwitch){
		if(IsColorChange){
			object->SetColor({1.f,1.f,1.f,1.f});
		}
		else if(!IsColorChange){
			object->SetColor({0.8f, 0.0f, 0.0f,1.0f});
		}
	}
}
