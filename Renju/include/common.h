//ͨ��ͷ�ļ� ����ÿ���ֶ����õ��ĺ����ͺ�
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define LENGTH 15   //���̳���
#define EMPTY 0		//��λ
#define BLACK 1 	//����	
#define WHITE 2		//����
#define NULLPOSITION 255 //��ʾ�ǿ�����λ��

//�л���� 1��2 2��1
#define CHANGE_PLAYER player ^= 0b11

typedef unsigned char Chess_point;
typedef unsigned short Line;
typedef unsigned long long Board_key;

typedef struct iNode {
	Chess_point position;	  //�ڵ��Ӧ�·�
	short history_score;      //��ʷ��÷֣���������
} Node;

typedef Node *Tree; //��

extern int g_i, g_j;	//��¼��ǰ����λ��
extern int player;    //��¼��ǰ��ֵ�������
extern int renju[LENGTH][LENGTH];   //������Ϊȫ�ֱ���
extern clock_t sort_time, generate_time ,time_e, time_b; //������ʱ�����
extern int node_num, num_zobrist;
extern int base[9];   //��ϣƥ��Ȩֵ  ������ �Ľ��ռ�Ϊ�Ľ��ƽ��λ����
extern Board_key zobrist[LENGTH][LENGTH][2];   //�û���(transposition table, TT)
extern Board_key now_key; //��ǰ��ֵ

extern Line g_last_buf[5];  //����仯ǰ��δ�ı���ŷ�����
extern Tree g_move;   //������һ�����õ��߷�

int within_range(int i); //��0-14��������
int in_range(int i, int j); //i, j����0��14��
int win(int i, int j); //�ж���Ӯ
int is_full(); //�ж�������û������
void set_point(int i, int j);
void reset_point(int i, int j);

#endif