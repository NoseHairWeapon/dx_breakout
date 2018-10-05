#include "entity.h"

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
	P[4] = VGet(m_position.x + m_size.x, m_position.y + m_size.y, 0.0);
}