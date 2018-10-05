#pragma once

#include <iostream>
using namespace std;

class Font{
	VECTOR position;
public:
	void fontSet(VECTOR _position);
	void fontDraw();
};