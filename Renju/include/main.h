#ifndef _MAIN_H_
#define _MAIN_H_

#include "../include/common.h"
extern int player_i;
extern int player_j;
//Ϊ��׷���ٶ� �����ռ�Ԥ�Ȼ����������
void init_rand();                     //��ʼ�������
void init_point_table();              //��ʼ�����ֱ�
void init_move_table();               //��ʼ���߷���
void init_bit_board();                //��ʼ��λ���̣�0��ʾ�����壬1��ʾδ����
void set_bit_board(int i, int j);     //λ��������

void set_board();                     //��ӡ����
void set();                           //���� 
void AI_set();                        //AI����

#endif