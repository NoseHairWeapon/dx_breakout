#include <iostream>
#include <DxLib.h>
#include "D_GAME.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

D_GAME G_frame;
GameState g_gamestate = GAME_TITLE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�T�C�Y�擾
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);		//�`���𗠉�ʂɐݒ�

	ChangeWindowMode(TRUE);

	//�}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	G_frame.LoadSound();

	//�L�[���������܂Ń��[�v���܂�
	//(���Ȃ݂ɃL�[���������܂ő҂��Ƃ́uwaitKey�v�Ƃ�����p�̊֐�������܂�)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();	//��ʂ�����
		switch (g_gamestate){
		case GAME_TITLE:
			G_frame.DrawGameTitle(WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case GAME_MAIN:
			//�I�u�W�F�N�g�X�V
			G_frame.Idle();
			//��ʕ`��
			G_frame.Display();
			break;
		case GAME_OVER:
			G_frame.GameOver();
			break;
		default:
			break;
		}

		ScreenFlip();	//����ʂ�\��ʂɔ��f
	}

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}
