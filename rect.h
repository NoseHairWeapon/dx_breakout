#pragma once

#include <DxLib.h>
#include<iostream>
using namespace std;

class Rect{
	int red, green, blue;
protected:
	VECTOR m_position;
	VECTOR m_size;
public:
	Rect();
	Rect(VECTOR const &_position, VECTOR const &_size);
	void draw();
	void update(int &x, int &y);
	void update(const VECTOR &_position, const VECTOR &_size);
	void color_table(const VECTOR &CV);
	bool intersect(VECTOR const &_point);
	bool intersect(Rect const &_rect);
};
