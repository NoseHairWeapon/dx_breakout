#pragma once
#include <iostream>
#include "entity.h"
using namespace std;

#define FONT_WEIGHT 8
#define FONT_HEIGHT 32

#define PADDLE_DEFAULT_WIDTH 64
#define PADDLE_DEFAULT_HEIGHT 8

#define BLOCK_COLUMN_MAX 14
#define BLOCK_ROW_MAX 8
#define BALL_X_SPEED_MAX (2.f)
#define BLOCK_HEIGHT 12

enum GameState{
	GAME_TITLE,
	GAME_MAIN,
	GAME_CLEAR,
	GAME_OVER
};

extern GameState g_gamestate;

enum{
	LEVEL_DEFAULT,
	LEVEL_HIT_4,
	LEVEL_HIT_12,
	LEVEL_HIT_ORANGE,
	LEVEL_HIT_RED,
	LEVEL_MAX
};

class D_GAME{

public:
	void DrawGameTitle(int x, int y);
	void Reshape(int x, int y);
	void Display();
	void Idle();
};
