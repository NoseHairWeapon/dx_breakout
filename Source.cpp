#include <iostream>
#include <DxLib.h>
#include "D_GAME.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

D_GAME G_frame;

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

	G_frame.Reshape(WINDOW_WIDTH, WINDOW_HEIGHT);

	//�L�[���������܂Ń��[�v���܂�
	//(���Ȃ݂ɃL�[���������܂ő҂��Ƃ́uwaitKey�v�Ƃ�����p�̊֐�������܂�)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�I�u�W�F�N�g�X�V
		G_frame.Idle();

		ClearDrawScreen();	//��ʂ�����
		//��ʕ`��
		G_frame.Display();
		
		//messageroop�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;	//�G���[���N�����烋�[�v�𔲂���
		}
		
		ScreenFlip();	//����ʂ�\��ʂɔ��f
	}

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}
