#ifndef _SET_H_
#define _SET_H_

/*
 *�������塢������ʾ������Ȼ����Խ���
 */

#include "./common.h"
#include "./bit_board.h"
#include "./evaluate.h"

#define LASTBLACK 3         //���µĺ���
#define LASTWHITE 4         //���µİ���

/* �������� */
void set_board();                               //��ӡ��ǰ���Ƶ�����
void print_piece(int i, int j);                 //��ӡ����
void player_set();                              //ÿ��һ������������������Ӧȫ�ֲ����޸�
void AI_set();                                  //AI����
void set();                                     //������� 
int lineLength(int i, int j, int dx, int dy);   //���ض�Ӧ�����Ӹ���
void get_input();                               //��ȡ�������
void new_set(int i, int j);                     //�õ�
void print_pos();                               //����
void judge_result();                            //�жϵ�ǰ���
int win(int i, int j);                          //�ж��Ƿ�Ӯ
void player_op();                               //��Ҳ���
void AI_op();                                   //���⿪ʼ����AI
int forbid(int i ,int j);                       //�жϽ���

/* ȫ�ֱ��� */
extern int now_score[];   //��ǰ��������
extern Line g_move_buf[]; //�����߷�����
extern char game_mode;         //��Ϸģʽ
#endif