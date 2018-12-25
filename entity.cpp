#include "entity.h"

Rect::Rect(VECTOR const &_position, VECTOR const &_size)
:m_position(_position)
, m_size(_size)
{
	isDead = false;
}

Rect::Rect()
{
	m_position = VGet(0.0f, 0.0f, 0.0f);
	m_size = VGet(0.0f, 0.0f, 0.0f);
	isDead = false;
}

void Rect::draw()
{
	unsigned int cr;

	cr = GetColor(red, green, blue);

	DrawBox(
		m_position.x,
		m_position.y,
		m_position.x + m_size.x -1 ,
		m_position.y + m_size.y -1 ,
		cr,
		TRUE);
}

void Rect::update(int &x, int &y)
{
	m_position.x = x - m_size.x / 2;
	m_position.y = y - m_size.y / 2;
}

void Rect::update(const VECTOR &_position, const VECTOR &_size)
{
	m_position = _position;
	m_size = _size;
}

void Rect::color_table(const VECTOR &_c)
{
	red = _c.x;
	green = _c.y;
	blue = _c.z;
}
bool Rect::intersect(VECTOR const &_point)
{
	if ((_point.x >= m_position.x)
		&& (_point.x < m_position.x + m_size.x)
		&& (_point.y >= m_position.y)
		&& (_point.y < m_position.y + m_size.y))
		return true;
	return false;
}

bool Rect::intersect(Rect const &_rect)
{
	if ((m_position.x + m_size.x >= _rect.m_position.x)
		&& (m_position.x < _rect.m_position.x + _rect.m_size.x)
		&& (m_position.y + m_size.y >= _rect.m_position.y)
		&& (m_position.y < _rect.m_position.y + _rect.m_size.y))
		return true;
	return false;
}

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

//‹éŒ`‚Ì’¸“_‚Æ‰~‚ÌÕ“Ë
bool Entity::lazerCollisionPoint(Ball const &_ball)
{
	Ball t;

	for (int i = 0; i < 4; i++){
		t.getRectPointParameter(P[i]);
		if (t.intersectBall(_ball))
			return true;
	}
	return false;
}

//‹éŒ`‚Ì•Ó‚Æ‰~‚ÌÕ“Ë
bool Entity::lazerCollisionVertical(Ball const &_ball)
{
	VECTOR pq, pm;
	float inner, pqd2, pmd2, phd2, d2, k;
	VECTOR Bpos;
	float r;
	r = _ball.popradius();
	
	Bpos = _ball.popPosition();
	const int n[][2] = { { 0, 1}, { 2, 3 } };
	for (int i = 0; i < 2; i++){
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

bool Entity::lazerCollisionHorizontal(Ball const &_ball)
{
	VECTOR pq, pm;
	float inner, pqd2, pmd2, phd2, d2, k;
	VECTOR Bpos;
	float r;
	r = _ball.popradius();

	Bpos = _ball.popPosition();
	const int n[][2] = { { 0, 2 }, { 1, 3 } };
	for (int i = 0; i < 2; i++){
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

bool Entity::lazerCollisionSide(Ball const &_ball)
{
	VECTOR pq, pm;
	float inner, pqd2, pmd2, phd2, d2, k;
	VECTOR Bpos;
	float r;
	r = _ball.popradius();

	Bpos = _ball.popPosition();
	const int n[][4] = { { 0, 1, 3,2 }, { 1,3,2,0 } };
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

//‹éŒ`‚Ì“à•”‚É‰~‚ª‚ ‚é‚©‚Ç‚¤‚©‚Ì”»’è
bool Entity::lazerCollisionInner(Ball const &_ball)
{
	VECTOR pp, pm;
	float inner, outer, theta[2];
	VECTOR Bpos;

	Bpos = _ball.popPosition();
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

//‰~‚Æ‹éŒ`‚Ì”»’è	¦¡‰ñ‚ÍŽg‚í‚È‚¢
bool Entity::LazerCollision(Ball const &_ball)
{
	bool(Entity::*lazer_collision[])(Ball const &_ball)
	{
		&Entity::lazerCollisionPoint,
		&Entity::lazerCollisionSide,
		&Entity::lazerCollisionInner,
	};

	for (int i = 0; i < 3; i++){
		if ((this->*lazer_collision[i])(_ball))
			return true;
	}
	return false;
}