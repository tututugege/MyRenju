#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

/*
 *������Ϸģʽ���
 */

#include "../include/common.h"
#include "../include/bit_board.h"
#include "../include/set.h"

/* �������� */
void PvsP();        //�˻���ս
void PvsAI();       //���˶�ս
void AIvsAI();      //������ս
void print_pos();   //����
void init_hash();   //��ʼ�����ֱ�
#endif