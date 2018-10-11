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
	virtual void update(int &x, int &y);
	virtual void update(const VECTOR &_position, const VECTOR &_size);
	void color_table(const VECTOR &CV);
	bool intersect(VECTOR const &_point);
	bool intersect(Rect const &_rect);
	//手動での変更、おそらく使わない。
	void pushposition(VECTOR const &v){ m_position = v; }
	void pushsize(VECTOR const &v){ m_size = v; }
};
