#ifndef _COMMON_H_
#define _COMMON_H_

/*
 *����ÿ���ֶ����õ��ĺ����ͺ�
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* ���̻��������� */
#define LINE_NUM 14         //�������
#define LENGTH 15   		//���̳���
#define EMPTY 0				//��λ
#define BLACK 1 		 	//����	
#define WHITE 2			 	//����
#define NULLPOSITION 255 	//��ʾ�ǿ�����λ��
#define LOSE_SCORE -1000002 //��Ǳذܵ㣬�ڵ����������޳�

/* ����任�� PAR��ˮƽ VERΪ��ֱ LEFTΪ����45�� RIGHTΪ����45�� */
#define PAR_I(i, j) j
#define PAR_J(i, j) i
#define VER_I(i, j) i
#define VER_J(i, j) j
#define LEFT_I(i, j) (i + j)
#define LEFT_J(i, j) (i + j < LENGTH) ? i : (LINE_NUM - j)
#define RIGHT_I(i, j) (j - i + LINE_NUM)
#define RIGHT_J(i, j) (j <= i) ? j : i

/* �л���� */
#define CHANGE_PLAYER player ^= 0b11; bool_player = bool_player ^ 1

/* ��ʡ�ڴ� ����ֻ��һ���ֽ� */
typedef unsigned char Chess_point;
/* ��bit������ һ��short16λ���ɱ�ʾһ�� ������Line */
typedef unsigned short Line;

/* ��¼һ���߷��Ľڵ�Node */
typedef struct iNode {
	Chess_point i;	   //�ڵ������i(ӳ�䵽��ʾ���ϵ���������������)
	Chess_point j;	   //�ڵ�������j(ӳ�䵽��ʾ���ϵ��������Ǻ�����)
	Chess_point left;  //������45��������б�
	Chess_point right; //������45������ĺ���
	int point_score;   //λ�õ÷� ��������
	int shape[4];	   //��Ӧ�ĸ����������
} Node;

typedef Node *Tree; //������

/* ȫ�ֱ��� */
extern int g_i, g_j;				//��¼��ǰ����λ��
extern int player;    				//��¼��ǰ��ֵ�������
extern int bool_player; 			//��¼�����˵Ĳ���ֵ����Ҫ������������
extern int renju[LENGTH][LENGTH];   //����renju(����)
extern clock_t sort_time, generate_time ,time_e, time_b; //������ʱ�����
extern int node_num;				//�ڵ�����
extern const int base[15];   		//��ϣƥ��Ȩֵ  ������ �Ľ��ռ�Ϊ�Ľ��ƽ��λ����
extern Line g_last_buf[5];  		//����仯ǰ��δ�ı���ŷ�����
extern Tree g_move;   				//������һ�����õ��߷�
extern int board_shape[][30];       //�������� 3����

/* �������� */
int within_range(int i); 			//�ж�i�Ƿ���0-14��������
int in_range(int i, int j); 		//�ж�i, j����0��14��
int win(int i, int j); 				//�ж��Ƿ�Ӯ
int is_full(); 						//�ж�������û������

#endif