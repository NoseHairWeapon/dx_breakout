#pragma once

#include "Rect.h"
#include "ball.h"

class Entity : public Rect{
	VECTOR P[4];
public:
	Entity(VECTOR const &_position, VECTOR const &_size);
	bool intersect(Ball const &_ball);
};