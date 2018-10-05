#include "rect.h"

Rect::Rect(VECTOR const &_position, VECTOR const &_size)
:m_position(_position)
, m_size(_size)
{
}

Rect::Rect()
{
	m_position = VGet(300.0f, 300.0f, 0.0f);
	m_size = VGet(100.0f, 100.0f, 0.0f);
}

void Rect::draw()
{
	unsigned int cr;

	cr = GetColor(red, green, blue);

	DrawBox(
		m_position.x,
		m_position.y,
		m_position.x + m_size.x,
		m_position.y + m_size.y,
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

void Rect::color_table(const VECTOR &CV)
{
	red = CV.x;
	green = CV.y;
	blue = CV.z;
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
