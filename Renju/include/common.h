//ͨ��ͷ�ļ�
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 15   //���̳���
#define EMPTY 0		//��λ
#define BLACK 1 	//����	
#define WHITE 2		//����
#define NULLPOSITION 255

typedef struct iNode {
	unsigned char position;	  //�ڵ��Ӧ�·�
	short history_score;
} Node;

typedef unsigned char Chess_point;
typedef unsigned short Line;
typedef unsigned long long Board_key;
typedef Node *Tree; //��

extern int g_i, g_j;
extern int player;    //��¼��ǰ��ֵ�������
extern int fir[LENGTH][LENGTH];   //������Ϊȫ�ֱ���
extern Board_key now_key; //��ǰ��ֵ
extern clock_t sort_time, generate_time ,time_e, time_b;
extern int node_num;
extern int base[9];   //��ϣƥ��Ȩֵ  ������
extern Board_key zobrist[LENGTH][LENGTH][2];   //�û���(transposition table, TT)

extern Line g_last_buf[5];
extern Tree g_move;

int within_range(int i); //��0-14��������
int in_range(int i, int j);
int win(int i, int j); //�ж���Ӯ
void change_player();  //����
int is_full();
void set_point(int i, int j);
void reset_point(int i, int j);

#endif