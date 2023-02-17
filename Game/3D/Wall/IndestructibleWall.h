#pragma once
#include "../BaseObjObject.h"
#include "../../Collision/MeshCollider.h"
#include "../../Collision/CollisionSystem/CollisionAttribute.h"

class IndestructibleWall : public BaseObjObject
{
//���S��̃��Z�b�g����
	const int DigAppearanceFrame = 50;
public:
	~IndestructibleWall();

	/// <summary>
	/// ������
	/// </summary>
	/// <returns></returns>
	void Initialize(ObjModelManager* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update(Camera* camera) override;

	/// <summary>
	/// 3D�`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// �㏈��
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	void OnCollision(const CollisionInfo& info) override;

	inline void IsNotAlive()	{IsAlive = false;}

	//Getter
	inline bool GetIsAlive()	{return IsAlive;}

	//Setter
	inline void SetPlayerPos(Vector3 pos)	{PlayerPos = pos;}

private:
	Vector3 PlayerPos;
	float distance = 0;

	//�G���A�Ŏg�p���Ȃ�
	bool IsAlive = true;
	//�����ɉ�������\��
	bool IsHide = false;

	bool IsCollision = false;
};
