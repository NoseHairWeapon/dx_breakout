#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <DxLib.h>
#include "ball.h"
#include <iostream>
using namespace std;

#define PI 3.141592
#define RTOD(RAD)	((RAD)*(180 / PI))
#define DTOR(DEG)	((DEG)*(PI / 180))

//矩形のクラス、あまり使わないと思う
class Rect{
	int red, green, blue;
public:
	VECTOR m_position;
	VECTOR m_size;
	bool isDead;
	Rect();
	Rect(VECTOR const &_position, VECTOR const &_size);
	void draw();
	virtual void update(int &x, int &y);
	virtual void update(const VECTOR &_position, const VECTOR &_size);
	void color_table(const VECTOR &_c);
	bool intersect(VECTOR const &_point);
	bool intersect(Rect const &_rect);
	//手動での変更、おそらく使わない。
	void pushposition(VECTOR const &v){ m_position = v; }
	void pushsize(VECTOR const &v){ m_size = v; }
};

//より実体を持った矩形
class Entity : public Rect{
	VECTOR P[4];
public:
	Entity();
	Entity(VECTOR const &_position, VECTOR const &_size);
	void update(VECTOR const &_position, VECTOR const &_size);
	void update(int &x, int &y);
	//ベクトル生成関数　簡略なのでヘッダーに書く
	VECTOR createVector(VECTOR const &p1, VECTOR const &p2)
	{
		return VGet(p2.x - p1.x, p2.y - p1.y, 0.0);	//p1->p2ベクトル
	}
	//ベクトルの内積
	float innerProduct(VECTOR const &a, VECTOR const &b)
	{
		return (a.x * b.x + a.y * b.y);	//a*b
	}

	//ベクトルの外積
	float outerProduct(VECTOR const &a, VECTOR const &b)
	{
		return (a.x * b.y - a.y * b.x);	//a×b
	}

	float VectorLength2(VECTOR const &vec)
	{
		return innerProduct(vec, vec);	// v*v = |v| ^ 2
	}

	bool lazerCollisionPoint(Ball const &_ball);
	bool lazerCollisionVertical(Ball const &_ball);
	bool lazerCollisionHorizontal(Ball const &_ball);
	bool lazerCollisionInner(Ball const &_ball);
	bool lazerCollisionSide(Ball const &_ball);
	bool LazerCollision(Ball const &_ball);
};

#endif
