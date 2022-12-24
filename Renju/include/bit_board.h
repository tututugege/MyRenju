#ifndef _BIT_BOARD_H_
#define _BIT_BOARD_H_

/*
 *λ���̲���,��Ҫ���������߷�������
 */

#include "../include/common.h"
#include "../include/set.h"
#include "../include/evaluate.h"

/* �궨�� */
#define MOVE_NUM 32768          //2^15,��ʾһ��15��������λ����������
#define NULL_SCORE 33554432     //�ŷ��ü��ı�־

/* �������� */
void init_move_table();                                                 //��ʼ���߷���ϣ��
void init_bit_board();                                                  //��ʼ��λ���̣�0��ʾ�����壬1��ʾδ����
Tree get_move(int i, int j, int depth, Line* last_buf, Tree last_move); //��ȡȫ���߷�           
int get_new_move(Tree move_set, Line* last_buf, int j, int depth);      //ÿ��һ����õ������߷�
void set_bit_board(int i, int j);                                       //��bit_board������
void buf_move_board(Line* buf);                                         //������һ����bit_move_board
void re_move_board(int j, Line* buf);                                   //�ָ���һ����bit_move_board
void get_range(int* start_j, int *end_j, int j);                        
int is_change(int, int, Tree);
void quick_sort(Tree move_set, int left, int right);                    //����

//Tree get_move_kill(int i, int j, int depth, Line* last_buf, Tree last_move); //��ȡ�����߷� �����ɱʹ�ã����ڵ��bug���ύ����ʱ����   

/* ȫ�ֱ��� */
/* bit_board��15��16bit��Line���ɣ�ÿһ��bitΪ1��ʾΪ�գ�Ϊ0��ʾ����*/
extern Line bit_board[];
/* bit_set��bit_boardÿһ�������Ӧ��ģ�壬ÿ�����嶼��Ҫ��Ӧ���л����*/
extern const Line bit_set[];
/* g_move_buf����һ���Ļ���bit_move_board*/
extern Line g_move_buf[LENGTH];

#endif