#ifndef _AI_H_
#define _AI_H

#include "../include/common.h"
#include "../include/set.h"
#include "../include/bit_board.h"

/* 宏定义 */
#define MAXDEPTH 8          //普通搜索深度
#define KILL_DEPTH 10       //算杀搜索深度
#define P_INFINITY 2000000  //评分上界
#define N_INFINITY -2000000 //评分下界

/* 函数声明 */
int alpha_beta(Tree pNode, unsigned short* last_buf, Tree last_move, int depth, int alpha, int beta); //alpha-beta剪枝算法
void AI_op();                                   //ai操作入口
void player_op();                               //读取对方操作进行一定的初始化修改
void set_point(Tree, int*);                     //下棋
void reset_point(Tree, int*);                   //悔棋
int pvs(Tree head, int depth);                  //主要变例搜索(PVS, Principal Variation Search)
void common_cut(Tree);                          //未冲棋状态下走法裁剪
int kill_cut(Tree);                             //冲棋状态下只需要搜索封堵点或成四成五点
void exchange(Tree move_set, int i, int j);     //交换两个node的值，用于排序
int get_line_num(int, int, int);                //获得某行某方向上棋子数目

#endif