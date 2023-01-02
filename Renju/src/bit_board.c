#include "./bit_board.h"

/*
 *λ����bit_board��15��short(2�ֽ�16λ)��� 0��ʾ��λ������
 *�߷�λ����bit_move_board�� 1��ʾΪ��ǰ�м�ֵ���߷�(����������������)
 *ÿ��һ����ͽ����е�bit_move_setģ������ǵ�λ������򼴿ɻ�����߷�
 *���л�������ɸ���bit_move_board
 *Ԥ�Ȼ����ϣ��move_table����������ֱ��ȡ���������ߵ�λ��
 *move_table����ÿ�е�λ����ֵΪ������ֱ�ӻ�����ߵ�λ�õĺ�����
 *64λlong long���Դ洢16��16������ ��˿���������15����ʾһ�е�15��λ���Ƿ��������
 *λ�����ٶȷǳ��죬����ʱ����һǧ����ڵ�����ʱ����100ms����
 */


int quick_select(Tree move_set, int left, int right);

unsigned long long move_table[MOVE_NUM]; //�߷������

/* ÿ�����嶼����Ӧ��ģ������Ӧ��5x5�������������*/
const Line bit_move_set[LENGTH][3] = {
	0b0111000000000000, 0b0110000000000000, 0b0101000000000000,
	0b0111100000000000, 0b0111000000000000, 0b0010100000000000,
	0b0111110000000000, 0b0011100000000000, 0b0101010000000000,
	0b0011111000000000, 0b0001110000000000, 0b0010101000000000,
	0b0001111100000000, 0b0000111000000000, 0b0001010100000000,
	0b0000111110000000, 0b0000011100000000, 0b0000101010000000,
	0b0000011111000000, 0b0000001110000000, 0b0000010101000000,
	0b0000001111100000, 0b0000000111000000, 0b0000001010100000,
	0b0000000111110000, 0b0000000011100000, 0b0000000101010000,
	0b0000000011111000, 0b0000000001110000, 0b0000000010101000,
	0b0000000001111100, 0b0000000000111000, 0b0000000001010100,
	0b0000000000111110, 0b0000000000011100, 0b0000000000101010,
	0b0000000000011111, 0b0000000000001110, 0b0000000000010101,
	0b0000000000001111, 0b0000000000000111, 0b0000000000001010,
	0b0000000000000111, 0b0000000000000011, 0b0000000000000101,
};

const Line bit_set[LENGTH] = {
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

Line bit_board[LENGTH] = {0};
Line bit_move_board[LENGTH] = {0};

/* ��ʼ��bit_board,ȫ������*/
void init_bit_board() {
	for (int i = 0; i < LENGTH; i++)
		bit_board[i] = ~0;
}

/* ��ʼ��move_table*/
void init_move_table() {
    int index1, index2, temp;
    unsigned long long val;

	g_move = (Tree)malloc(sizeof(Node) * 2);
	g_move->i = 7;
	g_move->j = 7;
    g_move->left = LEFT_I(7, 7);
    g_move->right = RIGHT_I(7, 7);
    for (index1 = 0; index1 < 4; index1++)
        g_move->shape[index1] = 0;
	(g_move + 1)->j = NULLPOSITION;
    g_move->point_score = 4;

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

/*��ȡ�߷�*/
Tree get_move(int i, int j, int depth, Line* last_buf, Tree last_move) {           
    time_b = clock();
    Tree move_set, p, q;
    int index;

    /*ֱ�������㹻���ڴ��һ��һ���������,�ڴ���������*/
    move_set = (Tree)malloc(sizeof(Node)*200); 
    index = get_new_move(move_set, last_buf, j, depth);  
    node_num += index;

    /*������߷���ֱ�Ӽ�����һ�����߷�
     *��Ҫȥ����һ���µ�λ��i, j*/
    for (p = move_set + index, q = last_move; (q->i != i || q->j != j) && q->j != NULLPOSITION; p++, q++, index++) {
        p->i = q->i;
        p->j = q->j;
        p->left = q->left;
        p->right = q->right;
        // if (is_change(i, j, q))
            get_point_score(p);
        // else {
        //     for (int index = 0; index < 4; index++)
        //         p->shape[index] = q->shape[index];
        //     p->point_score = q->point_score;
        // }
    }
    if (q->j != NULLPOSITION) {
        q++;
        for (; q->j != NULLPOSITION; p++, q++, index++){
            p->i = q->i;
            p->j = q->j;
            p->left = q->left;
            p->right = q->right;
            // if (is_change(i, j, q))
                get_point_score(p);
            // else {
            //     for (int index = 0; index < 4; index++)
            //         p->shape[index] = q->shape[index];
            //     p->point_score = q->point_score;
            // }
        }
    }

    p->j = NULLPOSITION;
    time_e = clock();
    generate_time += time_e - time_b;
    time_b = clock();
    if (index > 15)
        quick_sort(move_set, 0, quick_select(move_set, 0, index - 1));
    else    
        quick_sort(move_set, 0, index - 1);
    time_e = clock();
    sort_time += time_e - time_b;

    return move_set;
}

/*���ݻ����buf�͵�ǰλ��5*5ȡ����ȡ����ȡ���߷�,�������߷���Ŀ*/
int get_new_move(Tree move_set, Line* last_buf, int j, int depth) {
    int start_j, end_j, i, index;
    unsigned long long val;
    Line new_move;

    index = 0;
    get_range(&start_j, &end_j, j);
    for (; start_j != end_j; start_j++) {
        /*ȡ���֮����λ���̽��������ӵ�λ������*/
        new_move = (bit_move_board[start_j] ^ last_buf[start_j]) & bit_board[start_j];
        val = move_table[new_move];
        while (val) {
            i = val & 0b1111;
            move_set[index].i = i;
            move_set[index].j = start_j;
            move_set[index].left = LEFT_I(i, start_j);
            move_set[index].right = RIGHT_I(i, start_j);
            get_point_score(move_set + index);
            val = val >> 4;
            index++;
        }
    }

    return index;
}

/* ijλ��������λ���̺��߷����̽��иĶ� */
void set_bit_board(int i, int j) {
    int start_j, end_j;
    int temp = j, index;

    get_range(&start_j, &end_j, j);
    start_j--;
    for (index = 0; temp != end_j; temp++, index++) {
        bit_move_board[temp] |= bit_move_set[i][index];
        bit_move_board[temp] &= bit_board[temp];
    }
    for (index = 1, j--; j != start_j; j--, index++) {
        bit_move_board[j] |= bit_move_set[i][index];
        bit_move_board[j] &= bit_board[j];
    }
}

/* �ָ�move_board */
void re_move_board(int j, Line* buf) {
    int start_j, end_j;

    get_range(&start_j, &end_j, j);
    for (; start_j != end_j; start_j++)
        bit_move_board[start_j] = buf[start_j];
}

/* ����move_board */
void buf_move_board(Line* buf) {
    for (int i = 0; i < LENGTH; i++) 
        buf[i] = bit_move_board[i];
}

/* ��ȡj�ķ�Χ����Ҫ��Ϊ�˿��Ǳ߽�������*/
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

/* �жϸõ��Ƿ�����һ����ͬһ�� �Դ��ж��Ƿ���Ҫ���µ����Ϣ */
int is_change(int i, int j, Tree p) {
    if (p->point_score == NULL_SCORE || p->point_score == LOSE_SCORE)
        return 1;

    int now_i = p->i;
    int now_j = p->j;
    int val;

    if ((now_i == i) || (now_j == j))
        return 1;

    if (abs(now_i - i) == abs(now_j - j))
        return 1;

    return 0;
}

/* ��Ȼ��������Ļ�ȡ�����߷����� */
// Tree get_move_kill(int i, int j, int depth, Line* last_buf, Tree last_move) {           
//     time_b = clock();
//     Tree move_set, p, q;
//     int index;

//     //ֱ�������㹻���ڴ��һ��һ���������
//     move_set = (Tree)malloc(sizeof(Node)*200); 
//     index = get_new_move(move_set, last_buf, j, depth);  
//     node_num += index;

//     //������߷���ֱ�Ӽ�����һ�����߷�
//     //��Ҫȥ����һ���µ�λ��
//     for (p = move_set + index, q = last_move; (q->i != i || q->j != j) && q->j != NULLPOSITION; p++, q++, index++) {
//         p->i = q->i;
//         p->j = q->j;
//         p->left = q->left;
//         p->right = q->right;
//         get_point_score(p);
//     }
//     if (q->j != NULLPOSITION) {
//         q++;
//         for (; q->j != NULLPOSITION; p++, q++, index++){
//             p->i = q->i;
//             p->j = q->j;
//             p->left = q->left;
//             p->right = q->right;
//             get_point_score(p);
//         }
//     }
//     p->j = NULLPOSITION;
//     time_e = clock();
//     generate_time += time_e - time_b;
//     time_b = clock();
//     quick_sort(move_set, 0, quick_select(move_set, 0, index - 1));
//     time_e = clock();
//     sort_time += time_e - time_b;
    
//     return move_set;
// }

