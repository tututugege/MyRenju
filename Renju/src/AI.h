#ifndef _AI_H_
#define _AI_H

#include "./common.h"
#include "./set.h"
#include "./bit_board.h"

/* �궨�� */
#define MAXDEPTH 9          //��ͨ�������
#define KILL_DEPTH 15       //��ɱ�������
#define P_INFINITY 2000000  //�����Ͻ�
#define N_INFINITY -2000000 //�����½�

/* �������� */
int alpha_beta(Tree pNode, unsigned short* last_buf, Tree last_move, int depth, int alpha, int beta); //alpha-beta��֦�㷨
int alpha_beta_kill(Tree pNode, unsigned short* last_buf, Tree last_move, int depth, int alpha, int beta); //alpha-beta��֦�㷨
void AI_op();                                   //ai�������
void player_op();                               //��ȡ�Է���������һ���ĳ�ʼ���޸�
void set_point(Tree, int*);                     //����
void reset_point(Tree, int*);                   //����
int pvs(Tree head, int depth);                  //��Ҫ��������(PVS, Principal Variation Search)
void common_cut(Tree);                          //δ����״̬���߷��ü�
int kill_cut(Tree);                             //����״̬��ֻ��Ҫ������µ����ĳ����
void exchange(Tree move_set, int i, int j);     //��������node��ֵ����������
int get_line_num(int, int, int);                //���ĳ��ĳ������������Ŀ
int quick_select(Tree move_set, int left, int right);

#endif