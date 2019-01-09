#include "Source.h"
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

D_GAME G_frame;
GameState g_gamestate = GAME_TITLE;

//time
int g_lasttime = 0;
int g_frametime = 0;
int g_timerstart;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�T�C�Y�擾
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);		//�`���𗠉�ʂɐݒ�
	g_lasttime = GetNowCount() & INT_MAX;	//���ݎ����̋L�^

	ChangeWindowMode(TRUE);

	//�}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	G_frame.Load();

	//�L�[���������܂Ń��[�v���܂�
	//(���Ȃ݂ɃL�[���������܂ő҂��Ƃ́uwaitKey�v�Ƃ�����p�̊֐�������܂�)
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		int curtime = GetNowCount();
		g_frametime = (float)(curtime - g_lasttime) / 1000.0f;
		g_lasttime = curtime;

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
		case GAME_CLEAR:
			G_frame.GameClear();
			break;
		default:
			break;
		}

		ScreenFlip();	//����ʂ�\��ʂɔ��f
	}

	//�ҋ@
	WaitKey();

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}
