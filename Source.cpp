#include <iostream>
#include <DxLib.h>
#include "D_GAME.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

D_GAME G_frame;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウサイズ取得
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);		//描画先を裏画面に設定

	ChangeWindowMode(TRUE);

	//マウスを表示状態にする
	SetMouseDispFlag(TRUE);

	G_frame.Reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

	//キーが押されるまでループします
	//(ちなみにキーが押されるまで待つことは「waitKey」という専用の関数があります)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//オブジェクト更新
		G_frame.Idle();

		ClearDrawScreen();	//画面を消す
		//画面描画
		G_frame.Display();
		
		//messageroopに代わる処理をする
		if (ProcessMessage() == -1)
		{
			break;	//エラーが起きたらループを抜ける
		}
		
		ScreenFlip();	//裏画面を表画面に反映
	}

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}
