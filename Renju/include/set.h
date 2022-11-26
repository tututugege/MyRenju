#ifndef _SET_H_
#define _SET_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY 0		//��λ
#define BLACK 1 	//����	
#define WHITE 2		//����
#define LASTBLACK 3 //���µĺ���
#define LASTWHITE 4 //���µİ���
#define LENGTH 15   //���̳���
#define NULLPOSITION 255

//λ����
#define BIT_0 0b111000000000000
#define BIT_1 0b111100000000000
#define BIT_2 0b111110000000000
#define BIT_3 0b011111000000000
#define BIT_4 0b001111100000000
#define BIT_5 0b000111110000000
#define BIT_6 0b000011111000000
#define BIT_7 0b000001111100000
#define BIT_8 0b000000111110000
#define BIT_9 0b000000011111000
#define BIT_10 0b000000001111100
#define BIT_11 0b000000000111110
#define BIT_12 0b000000000011111
#define BIT_13 0b000000000001111
#define BIT_14 0b000000000000111

typedef struct iNode {
	unsigned char position;	  //�ڵ��Ӧ�·�
	short history_point;
} Node;

typedef unsigned short line;

typedef Node *tree; //��

extern int player;    //��¼��ǰ��ֵ�������
extern int fir[LENGTH][LENGTH];   //������Ϊȫ�ֱ���
extern line bit_board[LENGTH];
extern unsigned long long now_key; //��ǰ��ֵ
extern int base[9];   //��ϣƥ��Ȩֵ  ������
extern unsigned long long zobrist[LENGTH][LENGTH][2];   //�û���(transposition table, TT)
extern int node_num;
extern line bit_board[LENGTH];
extern line bit_move_board[LENGTH];
extern line bit_set[LENGTH];
extern line g_last_buf[5];
extern tree g_move;

int is_full();
int forbid(int i ,int j);//�жϽ���
int win(int i, int j); //�ж���Ӯ
int within_range(int i); //��0-14��������
void change_player();  //����
void set_point(int i, int j);
void reset_point(int i, int j);

#endif