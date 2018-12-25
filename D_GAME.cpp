#include "D_GAME.h"
#include "entity.h"
#include <DxLib.h>
#include "ball.h"
#include <wincon.h>

//パワーテーブル
float powerTbl[] = {
	2,
	3,
	4,
	5,
	6
};

Rect field;
Entity Paddle;
Entity blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
VECTOR WindowSize;
VECTOR Color;
VECTOR v;
Ball ball;
VECTOR vec;					//使いまわしまくる変数

BOOL g_akey_prev;
int turn = 1;
int score = 0;
int Se_block, Se_wall, Se_paddle;
int level = LEVEL_DEFAULT;

bool started;

int getBlockCount(){
	int n = 0;
	for (int i = 0; i < BLOCK_ROW_MAX; i++){
		for (int j = 0; j < BLOCK_COLUMN_MAX; j++){
			if (!blocks[i][j].isDead)
				n++;
		}
	}
	return n;
}

//キートリガー処理
BOOL IsAKeyTrigger(int key){
	if (key & PAD_INPUT_A){
		if (g_akey_prev == FALSE){
			g_akey_prev = TRUE;
			return TRUE;
		}
	}
	else {
		g_akey_prev = FALSE;
	}
	return FALSE;
}

void D_GAME::DrawGameTitle(int x, int y)
{
	//フォント
	int g_middlefont;			//中サイズフォントハンドル
	int g_largefont;			//大サイズフォントハンドル
	int g_smallfont;			//小サイズフォントハンドル

	g_middlefont = CreateFontToHandle("メイリオ", 42, -1, DX_FONTTYPE_ANTIALIASING);
	g_largefont = CreateFontToHandle("メイリオ", 90, -1, DX_FONTTYPE_ANTIALIASING);
	g_smallfont = CreateFontToHandle("メイリオ", 18, -1, DX_FONTTYPE_ANTIALIASING);
	DrawStringToHandle(100, 400, "Zキーでゲームスタート",
		GetColor(255, 0, 255), g_middlefont);
	//キーをチェックして画面を切り替え
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (IsAKeyTrigger(key) == TRUE) {
		g_gamestate = GAME_MAIN;
		Reshape(x, y);
	}
}

void D_GAME::Reshape(int width, int height)
{
	Se_block = LoadSoundMem("decision1.mp3");
	Se_wall = LoadSoundMem("decision2.mp3");
	Se_paddle = LoadSoundMem("decision3.mp3");
	VECTOR ball_Initposition;
	VECTOR blockSize = VGet(field.m_size.x / BLOCK_COLUMN_MAX, 8, 0);
	//デバッグ表示
	//printfDx("width: %d, height: %d", width, height);
	//ScreenFlip();
	WindowSize = VGet(width, height, 0);

	float frameHeight = 16;
	field.m_size.y = WindowSize.y - frameHeight;
	field.m_size.x = field.m_size.y;
	field.m_position.x = (WindowSize.x - field.m_size.x) / 2;
	field.m_position.y = frameHeight;

	//ボールの半径設定
	ball.pushradius(8);
	//ボールの位置設定
	ball_Initposition = VGet(field.m_position.x, field.m_position.y + field.m_size.y / 2, 0.0);
	ball.pushPosition(ball_Initposition);
	v = VGet(1.0, 1.0, 0.0);
	ball.pushSpeed(v);
	ball.pushPower(powerTbl[level]);

	vec = VGet(field.m_position.x + field.m_size.x / 2 - (PADDLE_DEFAULT_WIDTH / 2), field.m_position.y + field.m_size.y - 64, 0.0);
	Paddle.pushposition(vec);
	vec = VGet(PADDLE_DEFAULT_WIDTH, PADDLE_DEFAULT_HEIGHT, 0.0);
	Paddle.pushsize(vec);

	//ブロック設定
	blockSize = VGet(field.m_size.x / BLOCK_COLUMN_MAX, BLOCK_HEIGHT, 0);
	float y = field.m_position.y + (FONT_HEIGHT + FONT_WEIGHT) * 2;
	for (int i = 0; i < BLOCK_ROW_MAX; i++)
	for (int j = 0; j < BLOCK_COLUMN_MAX; j++){
		vec = VGet((field.m_position.x + field.m_size.x * j / BLOCK_COLUMN_MAX),
			(y + i * blockSize.y) + 1, 0);
		blocks[i][j].pushposition(vec);
		blocks[i][j].pushsize(blockSize);
	}
}

void D_GAME::Display()
{
	//枠の色
	int Cr = GetColor(255, 255, 255);
	DrawBox(
		field.m_position.x - 8, 0,
		field.m_position.x + field.m_size.x + 8, WindowSize.y, Cr, TRUE);
		
	//フィールド描画
	Color = VGet(0, 0, 0);
	field.color_table(Color);
	field.draw();


		VECTOR Palette[4];
		Palette[0] = VGet(255, 0, 0);
		Palette[1] = VGet(255, 100, 0);
		Palette[2] = VGet(0, 255, 0);
		Palette[3] = VGet(255, 255, 0);
		//ブロック描画
		for (int i = 0; i < BLOCK_ROW_MAX; i++){
			for (int j = 0; j < BLOCK_COLUMN_MAX; j++){
				if (blocks[i][j].isDead)
					continue;
				blocks[i][j].color_table(Palette[i/2]);
				blocks[i][j].draw();
				/*Cr = GetColor(255, 255, 255);
				DrawBox(
				blocks[i][j].m_position.x + 1,
				blocks[i][j].m_position.y + 1,
				blocks[i][j].m_position.x + blocks[i][j].m_size.x + 1,
				blocks[i][j].m_position.y + blocks[i][j].m_size.y + 1,
				Cr,
				true);
				*/
			}
		}

	//ボール描画
	Color = VGet(255, 255, 255);
	ball.color_table(Color);
	ball.draw();

	Color = VGet(0, 200, 255);
	Paddle.color_table(Color);
	Paddle.draw();

	SetFontSize(FONT_HEIGHT);
	SetFontThickness(FONT_WEIGHT);

	float x = field.m_position.x,
		y = field.m_position.y;
	Cr = GetColor(255, 255, 255);
	DrawFormatString(x, y, Cr, "1");
	DrawFormatString(x + field.m_size.x / 2, y, Cr, "%d", turn);
	y += FONT_HEIGHT + FONT_WEIGHT;
	x += FONT_HEIGHT;
	{
		static unsigned int frame;
		if ((++frame / 15) % 2)
			DrawFormatString(x, y, Cr, "%03d",score);
	}
	DrawFormatString(x + field.m_size.x / 2, y, Cr, "000");
	y += (BLOCK_HEIGHT * BLOCK_ROW_MAX) + FONT_HEIGHT + FONT_WEIGHT;
	x = field.m_position.x;
	SetFontSize(16);
	SetFontThickness(2);
	DrawFormatString(x, y, Cr, "level: %d\n", level);
	y += 16;
	DrawFormatString(x, y, Cr, "BlockCount: %d\n", getBlockCount());
}

void D_GAME::Idle()
{
	int mouseX, mouseY;
	//マウスを表示状態にする
	SetMouseDispFlag(TRUE);

	GetMousePoint(&mouseX, &mouseY);
	mouseY = field.m_size.y - 64;			//Y座標は固定するため

	ball.pushPower(powerTbl[level]);

	ball.update();
	Paddle.update(mouseX, mouseY);

	//paddleの移動範囲制限
	if (Paddle.m_position.x <= field.m_position.x){
		Paddle.m_position.x = field.m_position.x;
		Paddle.update(Paddle.m_position,Paddle.m_size);
	}
	if (Paddle.m_position.x + Paddle.m_size.x >= field.m_position.x + field.m_size.x){
		Paddle.m_position.x = field.m_position.x + field.m_size.x - PADDLE_DEFAULT_WIDTH;
		Paddle.update(Paddle.m_position, Paddle.m_size);
	}

	if ((ball.m_position.x < field.m_position.x) ||(ball.m_position.x >= field.m_position.x + field.m_size.x)){
		ball.m_position = ball.m_lastposition;
		ball.m_speed.x *= -1;
		StopSoundMem(Se_paddle);
		StopSoundMem(Se_block);
		PlaySoundMem(Se_wall, DX_PLAYTYPE_BACK);
	}
	if ((ball.m_position.y < field.m_position.y)||(ball.m_position.y >= field.m_position.y + field.m_size.y)){
		ball.m_position = ball.m_lastposition;
		ball.m_speed.y *= -1;
		StopSoundMem(Se_paddle);
		StopSoundMem(Se_block);
		PlaySoundMem(Se_wall, DX_PLAYTYPE_BACK);
	}

	if (Paddle.lazerCollisionHorizontal(ball) || Paddle.lazerCollisionPoint(ball)){
		ball.m_position = ball.m_lastposition;
		ball.m_speed.y *= -1;
		StopSoundMem(Se_block);
		StopSoundMem(Se_wall);

		float paddleCenterX = Paddle.m_position.x + Paddle.m_size.x / 2;
		float sub = ball.m_position.x - paddleCenterX;
		float subMax = Paddle.m_size.x / 2;
		ball.m_speed.x = sub / subMax * BALL_X_SPEED_MAX;
		PlaySoundMem(Se_paddle, DX_PLAYTYPE_BACK);
	}

	for (int i = 0; i < BLOCK_ROW_MAX; i++){
		for (int j = 0; j < BLOCK_COLUMN_MAX; j++){
			if (blocks[i][j].isDead)
				continue;

			if (blocks[i][j].intersect(ball.m_position)){
				blocks[i][j].isDead = true;
				ball.m_speed.y *= -1;
				StopSoundMem(Se_paddle);
				StopSoundMem(Se_wall);

				int colorIdx = 3 - (i / 2);
				printfDx("colorIdx: %d\n", colorIdx);
				int s = 1 + 2 * colorIdx;
				score += s;
				PlaySoundMem(Se_block, DX_PLAYTYPE_BACK);

				{
					int n = getBlockCount();
					int blockCountMax = BLOCK_COLUMN_MAX * BLOCK_ROW_MAX;
					if (n <= blockCountMax - 4 && (level < LEVEL_HIT_4)){
						level = LEVEL_HIT_4;
					}
					if (n <= blockCountMax - 12 && (level < LEVEL_HIT_12)){
						level = LEVEL_HIT_12;
					}
					if ((colorIdx == 2) && (level < LEVEL_HIT_ORANGE)){
						level = LEVEL_HIT_ORANGE;
					}
					if ((colorIdx == 3) && (level < LEVEL_HIT_RED)){
						level = LEVEL_HIT_RED;
					}
				}
			}
		}
	}
}
