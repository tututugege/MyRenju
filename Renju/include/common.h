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
	short history_point;
} Node;

typedef unsigned short line;
typedef Node *tree; //��

extern int g_i, g_j;
extern int player;    //��¼��ǰ��ֵ�������
extern int fir[LENGTH][LENGTH];   //������Ϊȫ�ֱ���
extern unsigned long long now_key; //��ǰ��ֵ
extern clock_t generate_time ,time_e, time_b;
extern int node_num;
extern int base[9];   //��ϣƥ��Ȩֵ  ������
extern unsigned long long zobrist[LENGTH][LENGTH][2];   //�û���(transposition table, TT)

extern line g_last_buf[5];
extern tree g_move;

int within_range(int i); //��0-14��������
int win(int i, int j); //�ж���Ӯ
void change_player();  //����
int is_full();
void set_point(int i, int j);
void reset_point(int i, int j);

#endif