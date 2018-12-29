#include "ball.h"

Ball::Ball()
{
	m_position.x = 320;
	m_position.y = 240;
	radius = 15;
	m_speed = VGet(0.0, 0.0, 0.0);
}

void Ball::update()
{
	VECTOR vec;
	vec.x = m_speed.x * m_power;
	vec.y = m_speed.y * m_power;
	vec.z = m_speed.z * m_power;
	m_lastposition = m_position;
	m_position = VAdd(m_position, vec);
}

void Ball::update(int &x, int &y)
{
	VECTOR vec;
	vec.x = m_speed.x * m_power;
	vec.y = m_speed.y * m_power;
	vec.z = m_speed.z * m_power;
	m_position.x = x;
	m_position.y = y;
	m_position.z = 0;
	m_lastposition = m_position;
	m_position = VAdd(m_position, vec);
}

void Ball::draw()
{
	int Cr;
	Cr = GetColor(red, green, blue);
	// ‰~‚ð•`‰æ
	DrawCircle(m_position.x, m_position.y, radius, Cr, TRUE);
}

void Ball::Speedfresh()
{
	m_speed = VGet(0.0, 0.0, 0.0);
}

void Ball::color_table(const VECTOR &_c)
{
	red = _c.x;
	green = _c.y;
	blue = _c.z;
}

void Ball::pushradius(int r)
{
	radius = r;
}

int Ball::popradius() const
{
	return radius;
}

void Ball::pushSpeed(VECTOR &vec)
{
	m_speed = VAdd(m_speed, vec);
}

void Ball::pushPower(float const &_power)
{
	m_power = _power;
}

bool Ball::intersectBall(const Ball &_ball)
{
	float dx, dy, r;
	float distance;

	dx = m_position.x - _ball.m_position.x;
	dy = m_position.y - _ball.m_position.y;
	r = (radius + _ball.radius) * (radius + _ball.radius);

	distance = (dx * dx) + (dy * dy);
	
	if (r > distance)
		return true;
	else 
		return false;
}

void Ball::getRectPointParameter(VECTOR const &position)
{
	m_position = position;
	radius = 0.0;
}

VECTOR Ball::popPosition() const
{
	return m_position;
}

void Ball::pushPosition(VECTOR const &_Vec)
{
	m_position = VGet(_Vec.x, _Vec.y, _Vec.z);
}