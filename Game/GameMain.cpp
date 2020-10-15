//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author�Ԗ� �M�l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"

#define DEMO 0
#define SERVE 1
#define IN_PLAY 2
#define WAIT 3

#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 28
#define PADDLE1_SPEED 5.0f
#define PADDLE2_SPEED 2.0f
#define BALL_SIZE 8
#define BALL_SPEED_X 4.0f
#define BALL_SPEED_Y 4.0f
// �O���[�o���ϐ��̒�` ====================================================
//�Q�[���̏��
int g_game_state;
//�^�C���J�E���g
int g_flame_count;
//�_���J�E���g
int g_count1;
int g_count2;
//�_���\��
HFNT g_point1;
HFNT g_point2;
//�{�[��
float g_ball_pos_x;
float g_ball_pos_y;
float g_ball_vel_x;
float g_ball_vel_y;
//�p�h��
float g_paddle1_pos_x;
float g_paddle1_pos_y;
float g_paddle1_vel_x;
float g_paddle1_vel_y;
//�p�h��CPU
float g_paddle2_pos_x;
float g_paddle2_pos_y;
float g_paddle2_vel_x;
float g_paddle2_vel_y;
//���̓f�o�C�X�̏��
int g_input_state;
int g_ball_state;

// �֐��̒�` ==============================================================
void UpdateDemo(void);
void UpdateServe(void);
void UpdateInPlay(void);
void UpdateWait(void);

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	//�f���v���C����X�^�[�g
	g_game_state = DEMO;

	g_flame_count = 0;
	g_count1 = 0;
	g_count2 = 0;

	g_point1 = CreateFontToHandle("HG�޼��E", 60, 5, DX_FONTTYPE_ANTIALIASING_4X4);
	g_point2 = CreateFontToHandle("HG�޼��E", 60, 5, DX_FONTTYPE_ANTIALIASING_4X4);

	g_ball_pos_x = SCREEN_CENTER_X;
	g_ball_pos_y = SCREEN_CENTER_Y;
	g_ball_vel_x = BALL_SPEED_X;
	g_ball_vel_y = BALL_SPEED_Y;

	g_paddle1_pos_x = SCREEN_RIGHT + 14;
	g_paddle1_pos_y = SCREEN_CENTER_Y;
	g_paddle1_vel_x = 0.0f;
	g_paddle1_vel_y = 0.0f;

	g_paddle2_pos_x = SCREEN_LEFT - 14;
	g_paddle2_pos_y = SCREEN_CENTER_Y;
	g_paddle2_vel_x = 0.0f;
	g_paddle2_vel_y = PADDLE2_SPEED;
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//���͏�Ԃ̎擾
	g_input_state = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	switch (g_game_state)
	{
	case DEMO:
		UpdateDemo();
		break;
	case SERVE:
		UpdateServe();
		break;
	case IN_PLAY:
		UpdateInPlay();
		break;
	case WAIT:
		UpdateWait();
		break;
	}




}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{
	//�{�[���̕`��
	int x1 = (int)(g_ball_pos_x - BALL_SIZE / 2);
	int y1 = (int)(g_ball_pos_y - BALL_SIZE / 2);
	int x2 = (int)(g_ball_pos_x + BALL_SIZE / 2);
	int y2 = (int)(g_ball_pos_y + BALL_SIZE / 2);
	DrawBox(x1, y1, x2, y2, COLOR_WHITE, 1);
	//�p�h���̕`��
	int x3 = (int)g_paddle1_pos_x - PADDLE_WIDTH / 2;
	int y3 = (int)g_paddle1_pos_y - PADDLE_HEIGHT / 2;
	int x4 = (int)g_paddle1_pos_x + PADDLE_WIDTH / 2;
	int y4 = (int)g_paddle1_pos_y + PADDLE_HEIGHT / 2;
	DrawBox(x3, y3, x4, y4, GetColor(50,100,150), 1);
	//CPU�p�h���̕`��
	int x5 = (int)g_paddle2_pos_x - PADDLE_WIDTH / 2;
	int y5 = (int)g_paddle2_pos_y - PADDLE_HEIGHT / 2;
	int x6 = (int)g_paddle2_pos_x + PADDLE_WIDTH / 2;
	int y6 = (int)g_paddle2_pos_y + PADDLE_HEIGHT / 2;
	DrawBox(x5, y5, x6, y6, GetColor(150, 50, 100), 1);

	DrawFormatStringToHandle(220, 20, COLOR_WHITE, g_point1, "%2d", g_count2);
	DrawFormatStringToHandle(380, 20, COLOR_WHITE, g_point2, "%2d", g_count1);
	DrawDashedLine(SCREEN_CENTER_X, SCREEN_TOP, SCREEN_CENTER_X, SCREEN_BOTTOM, COLOR_WHITE, 9, 3);
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{

}


void UpdateDemo(void)
{
	float ball_left;
	float ball_right;
	float ball_top;
	float ball_bottom;

	g_paddle1_pos_x = SCREEN_RIGHT + 14;
	g_paddle2_pos_x = SCREEN_LEFT - 14;

	//�㉺���E�����蔻��
	ball_left = g_ball_pos_x - BALL_SIZE / 2;
	ball_right = g_ball_pos_x + BALL_SIZE / 2;
	ball_top = g_ball_pos_y - BALL_SIZE / 2;
	ball_bottom = g_ball_pos_y + BALL_SIZE / 2;
	//�{�[���ǔ���
	if (ball_left < SCREEN_LEFT || ball_right > SCREEN_RIGHT)
	{
		g_ball_vel_x = -g_ball_vel_x;
	}
	if (ball_top < SCREEN_TOP || ball_bottom >= SCREEN_BOTTOM)
	{
		g_ball_vel_y = -g_ball_vel_y;
	}

	g_ball_pos_x += g_ball_vel_x;
	g_ball_pos_y += g_ball_vel_y;

	DrawFormatString(200, 320, COLOR_WHITE ,"Press [Enter] to Start");

	if (g_input_state &  PAD_INPUT_10)
	{
		g_count1 = 0;
		g_count2 = 0;
		g_game_state = SERVE;
	}
}

void UpdateServe(void)
{
	float paddle1_top;
	float paddle1_bottom;
	float paddle1_left;
	float paddle1_right;

	g_ball_state = 0;
	g_ball_pos_x = SCREEN_CENTER_X;
	g_paddle1_pos_x = SCREEN_RIGHT - (PADDLE_WIDTH / 2 + 64);
	g_paddle2_pos_x = SCREEN_LEFT + (PADDLE_WIDTH / 2 + 64);
	paddle1_top = g_paddle1_pos_y - PADDLE_HEIGHT / 2;
	paddle1_bottom = g_paddle1_pos_y + PADDLE_HEIGHT / 2;
	paddle1_left = g_paddle1_pos_x - PADDLE_WIDTH / 2;
	paddle1_right = g_paddle1_pos_x + PADDLE_WIDTH / 2;
	//�L�[����
	if ((g_input_state & PAD_INPUT_UP) != 0) {
		g_paddle1_vel_y = -PADDLE1_SPEED;
	}
	else if ((g_input_state & PAD_INPUT_DOWN) != 0) {
		g_paddle1_vel_y = PADDLE1_SPEED;
	}
	else {
		g_paddle1_vel_y *= 0.8f;
	}
	if ((g_input_state & PAD_INPUT_LEFT) != 0) {
		g_paddle1_vel_x = -PADDLE1_SPEED;
	}
	else if ((g_input_state & PAD_INPUT_RIGHT) != 0) {
		g_paddle1_vel_x = PADDLE1_SPEED +2;
	}
	else {
		g_paddle1_vel_x *= 0.8f;
	}
	g_paddle1_pos_x += g_paddle1_vel_x;
	g_paddle1_pos_y += g_paddle1_vel_y;
	//�p�h���͂ݏo����㉺�[�ɖ߂�
	if (paddle1_top < SCREEN_TOP) {
		g_paddle1_pos_y = SCREEN_TOP + PADDLE_HEIGHT / 2;
	}
	if (paddle1_bottom > SCREEN_BOTTOM) {
		g_paddle1_pos_y = SCREEN_BOTTOM - PADDLE_HEIGHT / 2;
	}
	if (g_paddle1_pos_x < SCREEN_CENTER_X + PADDLE_WIDTH / 2) {
		g_paddle1_pos_x = SCREEN_CENTER_X + PADDLE_WIDTH / 2;
	}
	if (g_paddle1_pos_x > SCREEN_RIGHT - PADDLE_WIDTH / 2) {
		g_paddle1_pos_x = SCREEN_RIGHT - PADDLE_WIDTH / 2;
	}

	g_flame_count++;
	if (g_flame_count > 180)
	{
		g_flame_count = 0;
		g_game_state = IN_PLAY;
	}
}

void UpdateInPlay(void)
{
	float ball_left;
	float ball_right;
	float ball_top;
	float ball_bottom;

	float paddle1_left;
	float paddle1_right;
	float paddle1_top;
	float paddle1_bottom;

	float paddle2_left;
	float paddle2_right;
	float paddle2_top;
	float paddle2_bottom;

	//�{�[�������t���[���Ńp�h���ɓ��B���邩
	float ball_move;
	//�{�[�����������ɂǂꂾ���i�ނ�
	float ball_vel_y_sum;
	//�Ō�ɏ㉺�ǔ��ˌ�ɂǂꂾ���i�ނ�
	float ball_reflect_move;
	//���˂�����
	int reflect_count;
	//�ŏI�I�Ƀp�h��������ׂ��ʒu
	float paddle2_pos_y_last;

	//�L�[����
	if ((g_input_state & PAD_INPUT_UP) != 0) {
		g_paddle1_vel_y = -PADDLE1_SPEED;
	}
	else if ((g_input_state & PAD_INPUT_DOWN) != 0) {
		g_paddle1_vel_y = PADDLE1_SPEED;
	}
	else {
		g_paddle1_vel_y *= 0.8f;
	}
	if ((g_input_state & PAD_INPUT_LEFT) != 0) {
		g_paddle1_vel_x = -PADDLE1_SPEED;
	}
	else if ((g_input_state & PAD_INPUT_RIGHT) != 0) {
		g_paddle1_vel_x = PADDLE1_SPEED + 2;
	}
	else {
		g_paddle1_vel_x *= 0.8f;
	}
	//���E�����蔻��
	ball_left = g_ball_pos_x - BALL_SIZE / 2;
	ball_right = g_ball_pos_x + BALL_SIZE / 2;
	paddle1_left = g_paddle1_pos_x - PADDLE_WIDTH / 2;
	paddle1_right = g_paddle1_pos_x + PADDLE_WIDTH / 2;
	paddle2_left = g_paddle2_pos_x - PADDLE_WIDTH / 2;
	paddle2_right = g_paddle2_pos_x + PADDLE_WIDTH / 2;
	//�㉺�����蔻��
	ball_top = g_ball_pos_y - BALL_SIZE / 2;
	ball_bottom = g_ball_pos_y + BALL_SIZE / 2;
	paddle1_top = g_paddle1_pos_y - PADDLE_HEIGHT / 2;
	paddle1_bottom = g_paddle1_pos_y + PADDLE_HEIGHT / 2;
	paddle2_top = g_paddle2_pos_y - PADDLE_HEIGHT / 2;
	paddle2_bottom = g_paddle2_pos_y + PADDLE_HEIGHT / 2;
	//�{�[���p�h�������蔻��
	if (ball_right > paddle1_left &&
		ball_left < paddle1_right &&
		ball_top < paddle1_bottom &&
		ball_bottom > paddle1_top &&
		g_ball_vel_x >0)
	{
		g_ball_vel_x = -g_ball_vel_x;
		g_ball_vel_y = (g_ball_pos_y - g_paddle1_pos_y) / 5;
	}
	//�{�[���ǔ���
	if (ball_left < SCREEN_LEFT)
	{
		g_count1++;
		if (g_count1 == 11)
		{
			g_game_state = WAIT;
		}
		else
		{
			g_game_state = SERVE;
		}
	}
	else if (ball_right > SCREEN_RIGHT)
	{
		g_count2++;
		if (g_count2 == 11)
		{
			g_game_state = WAIT;
		}
		else
		{
			g_game_state = SERVE;
		}
	}
	if (ball_top < SCREEN_TOP || ball_bottom >= SCREEN_BOTTOM)
	{
		g_ball_vel_y = -g_ball_vel_y;
	}

	//�{�[�������ɓ����Ă���Ƃ���CPU�p�h���\��
	if (g_ball_vel_x < 0)
	{
		//�p�h�����x�̏�����
		g_paddle2_vel_y = PADDLE2_SPEED;
		//�{�[�������t���[���Ńp�h���ɓ��B���邩
		ball_move = (paddle2_right - ball_left) / g_ball_vel_x;
		//�{�[�����������ɂǂꂾ���i�ނ�
		ball_vel_y_sum = g_ball_vel_y * ball_move;

		//�{�[���̃p�h�����B�ʒu�v�Z�@if�������Ȃ�
		if (ball_vel_y_sum > 0)
		{
			//�{�[�����Ō�ɔ��˂���ǂ���ǂ��܂œ����̂�
			ball_reflect_move = (int)(ball_vel_y_sum - (SCREEN_BOTTOM - ball_bottom)) % SCREEN_BOTTOM;
			reflect_count = (int)((ball_vel_y_sum - (SCREEN_BOTTOM - ball_bottom)) / SCREEN_BOTTOM);
			if (reflect_count == 0) {
				if (ball_reflect_move > 0) {
					paddle2_pos_y_last = SCREEN_BOTTOM - ball_reflect_move;
				}
				else {
					paddle2_pos_y_last = SCREEN_BOTTOM + ball_reflect_move;
				}
			}
			else {
				if (reflect_count % 2 == 0) {	//�ŏI�I�Ƀp�h�������B���ׂ����W
					paddle2_pos_y_last = SCREEN_BOTTOM - ball_reflect_move;
				}
				else {
					paddle2_pos_y_last = SCREEN_TOP + ball_reflect_move;
				}
			}
		}
		else {
			ball_reflect_move = (int)(ball_vel_y_sum + ball_top) % SCREEN_BOTTOM;
			reflect_count = (int)((ball_vel_y_sum + ball_top) / SCREEN_BOTTOM);
			if (reflect_count == 0) {
				if (ball_reflect_move > 0) {
					paddle2_pos_y_last = ball_reflect_move;
				}
				else {
					paddle2_pos_y_last = -ball_reflect_move;
				}
			}
			else {
				if (reflect_count % 2 == 0) {	//�ŏI�I�Ƀp�h�������B���ׂ����W
					paddle2_pos_y_last = -ball_reflect_move;
				}
				else {
					paddle2_pos_y_last = SCREEN_BOTTOM + ball_reflect_move;
				}
			}
		}

		//((�����ړI���W���p�h�����W������ɓ���)||(���̋t))de�p�h���ړ��������t��
		if ((paddle2_pos_y_last > g_paddle2_pos_y && g_paddle2_vel_y < 0) || (paddle2_pos_y_last < g_paddle2_pos_y && g_paddle2_vel_y > 0))
		{
			g_paddle2_vel_y = -g_paddle2_vel_y;
		}
		else if (paddle2_pos_y_last > paddle2_top && paddle2_pos_y_last < paddle2_bottom)
		{
			g_paddle2_vel_y = 0;
		}
		//�����蔻��
		if (ball_right > paddle2_left && ball_left < paddle2_right && ball_top < paddle2_bottom && ball_bottom > paddle2_top)
		{
			g_ball_vel_x = -g_ball_vel_x;
			g_ball_vel_y = (g_ball_pos_y - g_paddle2_pos_y) / 5;
		}
	}
	else {
		g_paddle2_vel_y = 0.0f;
	}
	g_paddle2_pos_x += g_paddle2_vel_x;
	g_paddle2_pos_y += g_paddle2_vel_y;

	g_paddle1_pos_x += g_paddle1_vel_x;
	g_paddle1_pos_y += g_paddle1_vel_y;

	g_ball_pos_x += g_ball_vel_x;
	g_ball_pos_y += g_ball_vel_y;
	//�p�h���͂ݏo����㉺�[�ɖ߂�
	if (g_paddle1_pos_y < SCREEN_TOP + PADDLE_HEIGHT / 2) {
		g_paddle1_pos_y = SCREEN_TOP + PADDLE_HEIGHT / 2;
	}
	if (g_paddle1_pos_y >= SCREEN_BOTTOM - PADDLE_HEIGHT / 2) {
		g_paddle1_pos_y = SCREEN_BOTTOM - PADDLE_HEIGHT / 2;
	}
	if (g_paddle1_pos_x < SCREEN_CENTER_X + PADDLE_WIDTH / 2) {
		g_paddle1_pos_x = SCREEN_CENTER_X + PADDLE_WIDTH / 2;
	}
	if (g_paddle1_pos_x > SCREEN_RIGHT - PADDLE_WIDTH / 2) {
		g_paddle1_pos_x = SCREEN_RIGHT - PADDLE_WIDTH / 2;
	}
	if (g_paddle2_pos_y < SCREEN_TOP + PADDLE_HEIGHT / 2) {
		g_paddle2_pos_y = SCREEN_TOP + PADDLE_HEIGHT / 2;
	}
	if (g_paddle2_pos_y >= SCREEN_BOTTOM - PADDLE_HEIGHT / 2) {
		g_paddle2_pos_y = SCREEN_BOTTOM - PADDLE_HEIGHT / 2;
	}
}

void UpdateWait(void)
{
	g_flame_count++;
	if (g_flame_count > 240)
	{

		g_flame_count = 0;
		g_game_state = DEMO;
		g_ball_pos_x = SCREEN_CENTER_X;
	}
}