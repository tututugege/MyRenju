#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

#include "../include/common.h"
#include "../include/bit_board.h"
#include "../include/zobrist.h"
#include "../include/set.h"

//Ϊ��׷���ٶ� �����ռ�Ԥ�Ȼ����������
void PvsP(); //�˻���ս
void PvsAI(); //���˶�ս
void AIvsAI(); //������ս
void print_pos(); //����

void init_point_table(); //��ʼ�����ֱ�

#endif