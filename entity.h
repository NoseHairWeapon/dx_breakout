#pragma once

#include "Rect.h"
#include "ball.h"

#define PI 3.141592
#define RTOD(RAD)	((RAD)*(180 / PI))
#define DTOR(DEG)	((DEG)*(PI / 180))

class Entity : public Rect{
	VECTOR P[4];
public:
	Entity();
	Entity(VECTOR const &_position, VECTOR const &_size);
	void update(VECTOR const &_position, VECTOR const &_size);
	void update(int &x, int &y);
	//�x�N�g�������֐��@�ȗ��Ȃ̂Ńw�b�_�[�ɏ���
	VECTOR createVector(VECTOR const &p1, VECTOR const &p2)
	{
		return VGet(p2.x - p1.x, p2.y - p1.y, 0.0);	//p1->p2�x�N�g��
	}
	//�x�N�g���̓���
	float innerProduct(VECTOR const &a, VECTOR const &b)
	{
		return (a.x * b.x + a.y * b.y);	//a*b
	}

	//�x�N�g���̊O��
	float outerProduct(VECTOR const &a, VECTOR const &b)
	{
		return (a.x * b.y - a.y * b.x);	//a�~b
	}

	float VectorLength2(VECTOR const &vec)
	{
		return innerProduct(vec, vec);	// v*v = |v| ^ 2
	}

	bool lazerCollision1(Ball const &_ball);
	bool lazerCollision2(Ball const &_ball);
	bool lazerCollision3(Ball const &_ball);
	bool LazerCollision(Ball const &_ball);
};