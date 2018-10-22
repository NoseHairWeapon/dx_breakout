#include "entity.h"

Entity::Entity()
{
	P[0] = VGet(m_position.x, m_position.y, 0.0);
	P[1] = VGet(m_position.x + m_size.x, m_position.y, 0.0);
	P[2] = VGet(m_position.x, m_position.y + m_size.y, 0.0);
	P[3] = VGet(m_position.x + m_size.x, m_position.y + m_size.y, 0.0);
}

Entity::Entity(VECTOR const &_position, VECTOR const &_size) : Rect(_position, _size)
{
	/*
	P[0]-----------P[1]
	|				|
	|				|
	|				|
	|				|
	P[2]-----------P[3]
	*/
	P[0] = VGet(m_position.x, m_position.y, 0.0);
	P[1] = VGet(m_position.x + m_size.x, m_position.y, 0.0);
	P[2] = VGet(m_position.x, m_position.y + m_size.y, 0.0);
	P[3] = VGet(m_position.x + m_size.x, m_position.y + m_size.y, 0.0);
}

void Entity::update(VECTOR const &_position, VECTOR const &_size)
{
	m_position = _position;
	m_size = _size;

	P[0] = VGet(m_position.x, m_position.y, 0.0);
	P[1] = VGet(m_position.x + m_size.x, m_position.y, 0.0);
	P[2] = VGet(m_position.x, m_position.y + m_size.y, 0.0);
	P[3] = VGet(m_position.x + m_size.x, m_position.y + m_size.y, 0.0);
}

void Entity::update(int &x, int &y)
{
	m_position.x = x - m_size.x / 2;
	m_position.y = y - m_size.y / 2;
	
	P[0] = VGet(m_position.x, m_position.y, 0.0);
	P[1] = VGet(m_position.x + m_size.x, m_position.y, 0.0);
	P[2] = VGet(m_position.x, m_position.y + m_size.y, 0.0);
	P[3] = VGet(m_position.x + m_size.x, m_position.y + m_size.y, 0.0);
}

bool Entity::lazerCollision1(Ball const &_ball)
{
	Ball t;

	for (int i = 0; i < 4; i++){
		t.getRectPointParameter(P[i]);
		if (t.intersectBall(_ball))
			return true;
	}
	return false;
}

bool Entity::lazerCollision2(Ball const &_ball)
{
	VECTOR pq, pm;
	float inner, pqd2, pmd2, phd2, d2, k;
	VECTOR Bpos;
	float r;
	r = _ball.pushradius();
	
	Bpos = _ball.pushposition();
	const int n[][4] = { { 0, 1, 3, 2 }, { 1, 3, 2, 0 } };
	for (int i = 0; i < 4; i++){
		pq = createVector(P[n[0][i]], P[n[1][i]]);	//0,1,3,2 : 1,3,2,0
		pm = createVector(P[n[0][i]], Bpos);

		inner = innerProduct(pq, pm);	//“àÏ
		//‘å‚«‚³‚Ì2æ
		pqd2 = VectorLength2(pq);
		pmd2 = VectorLength2(pm);

		k = inner / pqd2;

		if (k < 0 || 1 < k) continue; //h‚ªü•ªpqã‚É‚ ‚é‚©‚Ç‚¤‚©

		phd2 = (inner * inner) / pqd2;	//ph‚Ì‘å‚«‚³‚Ì2æ
		d2 = pmd2 - phd2;	//‚ü‚Ì‘å‚«‚³‚Ì“ñæ

		if (d2 < r * r) return true;
	}
	return false;
}

bool Entity::lazerCollision3(Ball const &_ball)
{
	VECTOR pp, pm;
	float inner, outer, theta[2];
	VECTOR Bpos;

	Bpos = _ball.pushposition();
	for (int i = 0; i < 2; i++)
	{
		pp = createVector(P[i * 3], P[1 + i]);	//0.1 : 3.2
		pm = createVector(P[i * 3], Bpos);

		inner = innerProduct(pp, pm);
		outer = outerProduct(pp, pm);

		theta[i] = RTOD(atan2(outer, inner));
	}

	if (0 <= theta[0] && theta[0] <= 90 &&
		0 <= theta[1] && theta[1] <= 90){
		return true;
	}

	return false;
}

bool Entity::LazerCollision(Ball const &_ball)
{
	bool(Entity::*lazer_collision[])(Ball const &_ball)
	{
		&Entity::lazerCollision1,
		&Entity::lazerCollision2,
		&Entity::lazerCollision3,
	};

	for (int i = 0; i < 3; i++){
		if ((this->*lazer_collision[i])(_ball))
			return true;
	}
	return false;
}