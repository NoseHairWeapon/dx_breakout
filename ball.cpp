#include "ball.h"

Ball::Ball()
{
	m_position.x = 320;
	m_position.y = 240;
	radius = 15;
}

void Ball::update()
{
	m_lastposition = m_position;
	m_position = VAdd(m_position, m_speed);
}

void Ball::update(int &x, int &y)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = 0;
}

void Ball::draw()
{
	int Cr;
	Cr = GetColor(red, green, blue);
	// ‰~‚ð•`‰æ
	DrawCircle(m_position.x, m_position.y, radius, Cr, TRUE);
}

void Ball::color_table(VECTOR _c)
{
	red = _c.x;
	green = _c.y;
	blue = _c.z;
}

int Ball::pushradius() const
{
	return radius;
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

VECTOR Ball::pushposition() const
{
	return m_position;
}