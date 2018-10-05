#include <iostream>
#include <cstdlib>
#include <DxLib.h>
#include "rect.h"
#include "ball.h"
using namespace std;

VECTOR VPOS, VSIZE;
Rect r1;
Ball ball, ball2;

int MouseX, MouseY;
VECTOR color;

void idle();
void display();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);		//描画先を裏画面に設定

	ChangeWindowMode(TRUE);

	//マウスを表示状態にする
	SetMouseDispFlag(TRUE);

	//キーが押されるまでループします
	//(ちなみにキーが押されるまで待つことは「waitKey」という専用の関数があります)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//オブジェクト更新
		idle();
		//画面描画
		display();

		//messageroopに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;	//エラーが起きたらループを抜ける
		}
	}

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}

void idle()
{
	//マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);
	ball2.update(MouseX, MouseY);

	//オブジェクトの衝突
	if (ball.intersectBall(ball2)){
		color = VGet(255,0,0);		//色の設定
	}else
		color = VGet(0, 255, 255);
	ball2.color_table(color);		//色の設定

	color = VGet(0, 255, 0);
	ball.color_table(color);
}
void display()
{
	ClearDrawScreen();		//画面を消す
	//r1を描画
	r1.draw();
	ball2.draw();
	ball.draw();

	ScreenFlip();		//裏画面を表画面に反映
}