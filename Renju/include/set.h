#ifndef _SET_H_
#define _SET_H_

#include "../include/common.h"
#define LASTBLACK 3 //���µĺ���
#define LASTWHITE 4 //���µİ���
//λ����
extern int player_i;
extern int player_j;

void cache_move_board();
void set_bit_board(int i, int j);
void get_range(int*, int*, int);

void get_input();
void print_piece(int i, int j);
void set_board();   //��ӡ��ǰ���Ƶ�����
void set();          //���� 
void AI_set();       //AI����
void new_set(int i, int j);

int forbid(int i ,int j);//�жϽ���

void AI_operation();//���⿪ʼ����AI

#endif