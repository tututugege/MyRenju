#ifndef _GAME_MODE_H_
#define _GAME_MODE_H_

/*
 *������Ϸģʽ���
 */

#include "./common.h"
#include "./bit_board.h"
#include "./set.h"

/* �������� */
void PvsP();        //�˻���ս
void PvsAI();       //���˶�ս
void AIvsAI();      //������ս
void print_pos();   //����
void init_hash();   //��ʼ�����ֱ�
#endif