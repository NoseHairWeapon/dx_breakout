#pragma once

#include <DxLib.h>
#include <iostream>
using namespace std;

#define RTOD(RAD)	((RAD)*(180 / PI))

class Ball{
	int red, green, blue;
	float radius;
	float m_power;
public:
	VECTOR m_speed;
	VECTOR m_lastposition;
	VECTOR m_position;
	Ball();
	void color_table(const VECTOR &_c);
	void update();
	void update(int &x, int &y);
	void draw();
	void pushradius(int r);
	int popradius() const;
	void pushSpeed(VECTOR &Vec);
	void pushPower(float const &_power);
	bool intersectBall(const Ball &_ball);
	bool collisionWall(VECTOR &vec1, VECTOR &vec2);
	void getRectPointParameter(VECTOR const &position);
	VECTOR popPosition() const;
	void pushPosition(VECTOR const &_Vec);
};