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
	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);		//�`���𗠉�ʂɐݒ�

	ChangeWindowMode(TRUE);

	//�}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);

	//�L�[���������܂Ń��[�v���܂�
	//(���Ȃ݂ɃL�[���������܂ő҂��Ƃ́uwaitKey�v�Ƃ�����p�̊֐�������܂�)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�I�u�W�F�N�g�X�V
		idle();
		//��ʕ`��
		display();

		//messageroop�ɑ��鏈��������
		if (ProcessMessage() == -1)
		{
			break;	//�G���[���N�����烋�[�v�𔲂���
		}
	}

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}

void idle()
{
	//�}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);
	ball2.update(MouseX, MouseY);

	//�I�u�W�F�N�g�̏Փ�
	if (ball.intersectBall(ball2)){
		color = VGet(255,0,0);		//�F�̐ݒ�
	}else
		color = VGet(0, 255, 255);
	ball2.color_table(color);		//�F�̐ݒ�

	color = VGet(0, 255, 0);
	ball.color_table(color);
}
void display()
{
	ClearDrawScreen();		//��ʂ�����
	//r1��`��
	r1.draw();
	ball2.draw();
	ball.draw();

	ScreenFlip();		//����ʂ�\��ʂɔ��f
}