#pragma once

#include <DxLib.h>
#include <iostream>
using namespace std;

class Ball{
	float m_radius;
	VECTOR m_lastposition;
	VECTOR m_position;
	VECTOR m_speed;
	int red, green, blue;
	float radius;
public:
	Ball();
	void color_table(VECTOR _c);
	void update();
	void update(int &x, int &y);
	void draw();
	int pushradius() const;
	bool intersectBall(const Ball &_ball);
	void getRectPointParameter(VECTOR const &position);
	VECTOR pushposition() const;
};