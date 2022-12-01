#include "../include/bit_board.h"

void sort(Tree move_set, int num);
void clear_killer();
unsigned long long move_table[MOVE_NUM];
Line bit_move_set[LENGTH] = {
	0b0111000000000000,
	0b0111100000000000,
	0b0111110000000000,
	0b0011111000000000,
	0b0001111100000000,
	0b0000111110000000,
	0b0000011111000000,
	0b0000001111100000,
	0b0000000111110000,
	0b0000000011111000,
	0b0000000001111100,
	0b0000000000111110,
	0b0000000000011111,
	0b0000000000001111,
	0b0000000000000111
};

Line bit_set[LENGTH] = {
	0b1011111111111111,
	0b1101111111111111,
	0b1110111111111111,
	0b1111011111111111,
	0b1111101111111111,
	0b1111110111111111,
	0b1111111011111111,
	0b1111111101111111,
	0b1111111110111111,
	0b1111111111011111,
	0b1111111111101111,
	0b1111111111110111,
	0b1111111111111011,
	0b1111111111111101,
	0b1111111111111110
};

Line bit_board[LENGTH];
Line bit_move_board[LENGTH] = {0};
Line g_last_buf[5] = {0};
Line killer_board[LENGTH] = {0};

//位棋盘bit_board由15个short(2字节16位)组成 0表示该位有棋子
//走法位棋盘bit_move_board中 1表示为当前有价值的走法(两步内有其他棋子)

//预先缓存move_table，根据索引直接取出该行能走的位置
//move_table中以每行的位棋盘值为索引，直接获得能走的位置的横坐标
//64位long long可以存储16个16进制数 因此可以用其中15个表示一行的15个位置是否可以下棋

void init_bit_board() {
	for (int i = 0; i < LENGTH; i++)
		bit_board[i] = ~0;
}

void init_move_table() {
    int index1, index2, temp;
    unsigned long long val;

    set_bit_board(7, 7);
	g_move = (Tree)malloc(sizeof(Node) * 2);
	g_move->position = 119;
	(g_move + 1)->position = NULLPOSITION;

    for (index1 = 0; index1 < MOVE_NUM; index1++) {
        temp = index1;
        val = 0;
        for (index2 = LENGTH - 1; index2 >= 0; index2--) {
            if (temp & 0x1) {
                val = val << 4;
                val += index2;
            }
            temp = temp >> 1;
        }
        move_table[index1] = val;
    }
}

//获取走法
Tree get_move(int position, int j, Line* last_buf, Tree last_move) {           
    clear_killer();
    time_b = clock();
    Tree move_set, p, q;
    int index;

    //直接申请足够大内存比一个一个申请更快
    move_set = (Tree)malloc(sizeof(Node)*200); 
    index = get_new_move(move_set, last_buf, j);  
    node_num += index;

    //获得新走法后直接加上上一步的走法
    //需要去除上一步下的位置
    for (p = move_set + index, q = last_move; q->position != position && q->position != NULLPOSITION; p++, q++, index++) {
        p->position = q->position;
        p->history_score = GET_HIS(position);
        //查历史表
    }
    if (q->position != NULLPOSITION) {
        q++;
        for (; q->position != NULLPOSITION; p++, q++, index++){
            p->position = q->position;
            p->history_score = GET_HIS(position);
            //查历史表
        }
    }

    p->position = NULLPOSITION;
    p->history_score = 0;
    time_e = clock();
    generate_time += time_e - time_b;
    time_b = clock();
    quick_sort(move_set, 0, index - 1);
    time_e = clock();
    sort_time += time_e - time_b;
 
    return move_set;
}

//根据缓存的buf和当前位置5*5取余内取异或获取新走法,返回新走法数目
int get_new_move(Tree move_set, Line* last_buf, int j) {
    int start_j, end_j, i, index, buf_j;
    unsigned long long val;
    Line new_move;
    int position;

    index = 0;
    get_range(&start_j, &end_j, j);
    for (buf_j = 0; start_j != end_j; start_j++, buf_j++) {
        //取异或之后用位棋盘将已有棋子的位置置零
        new_move = (bit_move_board[start_j] ^ last_buf[buf_j]) & bit_board[start_j];
        val = move_table[new_move];
        while (val) {
            i = val & 0b1111;
            move_set[index].position = position =  i*(LENGTH + 1) + start_j;
            move_set[index].history_score = GET_HIS(position);
            val = val >> 4;
            index++;
        }
    }

    return index;
}

//ij位置下棋后对位棋盘和走法棋盘进行改动
void set_bit_board(int i, int j) {
    int start_j, end_j;

    get_range(&start_j, &end_j, j);
    bit_board[j] &= bit_set[i];
    for (; start_j != end_j; start_j++) {
        bit_move_board[start_j] |= bit_move_set[i];
        bit_move_board[start_j] &= bit_board[start_j];
    }
}

void re_bit_move(int j, Line* buf) {
    int start_j, end_j, i;

    get_range(&start_j, &end_j, j);
    for (i = 0; start_j != end_j; start_j++, i++)
        bit_move_board[start_j] = buf[i];
}

void buf_bit_move(int j, Line* buf) {
    int start_j, end_j, i;

    get_range(&start_j, &end_j, j);
    for (i = 0; start_j != end_j; start_j++, i++) 
        buf[i] = bit_move_board[start_j];
}

//获取j的范围（主要是为了考虑边界的情况）
void get_range(int *pstart_j, int *pend_j, int j) {
    switch (j) {
    case 0: 
        *pstart_j = 0;
        *pend_j = 3;
        break;
    case 1:
        *pstart_j = 0;
        *pend_j = 4;
        break;
    case 13:
        *pstart_j = 11;  
        *pend_j = 15;  
        break;
    case 14:
        *pstart_j = 12;
        *pend_j = 15;
        break;
    default:
        *pstart_j = j - 2;
        *pend_j = j + 3;
        break;
    }
}

void cache_move_board() {
    int start_j, end_j, i;
    get_range(&start_j, &end_j, g_j);    
    for (i = 0; start_j != end_j; i++, start_j++)
        g_last_buf[i] = bit_move_board[start_j];
}

void sort(Tree move_set, int num) {
    int i, j;
    i = 0;
    j = num;

    // for (Tree p = move_set; p->position != NULLPOSITION; p++)
    //     printf("%d ", p->history_score);
    // printf("\n");

    while (i < j) {
        while (move_set[i].history_score != 0)
            i++;
        while (move_set[j].history_score == 0) 
            j--;
        if (i < num && j > 0)
            exchange(move_set, i, j);
    }
    // for (Tree p = move_set; p->position != NULLPOSITION; p++)
    //     printf("%d ", p->history_score);
    // printf("\n");
    // system("pause");
    
    quick_sort(move_set, 0, i--);
    // for (Tree p = move_set; p->position != NULLPOSITION; p++)
    //     printf("%d ", p->history_score);
    // printf("\n");
    // system("pause");

}

void clear_killer() {
    for (int i = 0; i < LENGTH; i++)
        killer_board[i] = 0;
}
