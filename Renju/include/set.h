#ifndef _SET_H_
#define _SET_H_

#include "../include/common.h"
#include "../include/bit_board.h"
#define LASTBLACK 3 //���µĺ���
#define LASTWHITE 4 //���µİ���
//λ����

extern int g_score;

void set_board();   //��ӡ��ǰ���Ƶ�����
void print_piece(int i, int j);
void player_set();
void AI_set();       //AI����
void set();          //���� 
int lineLengTH(int i, int j, int dx, int dy);
void get_input();
void new_set(int i, int j);
void print_pos();
void judge_result();
int win(int i, int j);

void player_op();
void AI_op();//���⿪ʼ����AI

int forbid(int i ,int j);//�жϽ���

int move_evaluate(int i, int j, int g_score, int depth);

#endif