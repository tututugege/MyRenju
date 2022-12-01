#ifndef _BIT_BOARD_H_
#define _BIT_BOARD_H_

#include "../include/common.h"
#include "../include/set.h"
#include "../include/history.h"
#define MOVE_NUM 32768

void init_move_table();
void init_bit_board();                //��ʼ��λ���̣�0��ʾ�����壬1��ʾδ����
Tree get_move(int position, int j, Line* last_buf, Tree last_move);           
int get_new_move(Tree move_set, Line* last_buf, int j);
void set_bit_board(int i, int j);
void buf_bit_move(int j, Line* buf);
void re_bit_move(int j, Line* buf);
void get_range(int* start_j, int *end_j, int j);
void cache_move_board();

extern Line bit_board[];
extern Line bit_set[];


#endif