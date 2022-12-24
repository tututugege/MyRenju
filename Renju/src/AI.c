#include "./AI.h"

int node_num = 0;               //�����ڵ���Ŀ
int now_score[2] = {4, 0};      //��ǰ����0����1�ĵ÷�
int next_score[2] = {0, 0};     //�����������һ�����ĵ÷�
int board_shape[4][30] = {0};   //�ĸ�������������
Line g_move_buf[LENGTH] = {0};  //������һ�߷��ı�������
Tree PV_p;                      //����ָ���ҵ�������߷�

clock_t generate_time, sort_time; //�����߷�ʱ�������ʱ��
clock_t time_b, time_e;           //��ʼb ����e

void player_op() {
    Tree head;
    head = get_move(g_i, g_j, 0, g_move_buf, g_move);
    free(g_move);
    g_move = head;
}

/* PVS ��֦�㷨 ������ֵ soft_fail */
int alpha_beta(Tree pNode, Line* last_buf, Tree last_move, int depth, int alpha, int beta) {
    Tree p, head;
    Line buf[LENGTH];
    int v, found_PV = 0, best = N_INFINITY;
    int shape_buf[4];
    int i = pNode->i, j = pNode->j;

    /* 1.�÷ֹ��ߵ�������жϽ���,���н��ַ����������ΪpNodeָ����һ����߷� */
    if (player == WHITE && pNode->point_score > 3600) { 
        if (forbid(i, j))
            return P_INFINITY;
        else
            renju[i][j] = BLACK;
    }

    /* 2.�ж���û���Ѿ�����,�������ظ�����*/
    if (win(i, j)) 
        return N_INFINITY;

    /* 3.���������ľ�,���ص�ǰ���� */
    if (depth <= 0){
        if(player == BLACK) 
            return now_score[0] - now_score[1];   
        else 
            return now_score[1] - now_score[0];   
    }

    /* 4.���������������˳��ݹ������Ļ�
     *   ��ȡ�߷���������ü�*/
    head = get_move(i, j, depth, last_buf, last_move);
    if (now_score[bool_player^1] > 2000) 
        kill_cut(head);
    else 
        common_cut(head);
    buf_move_board(buf);

    /* 5.���������߷�
     *   ������ڽ�����һ��ۻ���*/
    for (p = head; p->point_score != NULL_SCORE; p++) {
        node_num++;
        i = p->i;
        j = p->j;
        set_bit_board(i ,j);
        set_point(p, shape_buf);
        //����ҵ�PV�߷� �ü�С����
        if (found_PV) {
            v = -alpha_beta(p, buf, head, depth - 1, -alpha - 1, -alpha);
            if (v > alpha && v < beta)
                v = -alpha_beta(p, buf, head, depth - 1, -beta, -alpha);
        } else 
            v = -alpha_beta(p, buf, head, depth - 1, -beta, -alpha);
        reset_point(p, shape_buf);
        re_move_board(j, buf);
        if (v > best) {
            best = v;
            if (v > alpha)
                alpha = v;
            if (v >= beta)
                break;
        }
    }
    /* 6.�ͷ�get_move��malloc�����head
     *   ������������best*/
    free(head);
    head = NULL;

    return best;
}

/* ��֦�㷨����ڣ�Ҳ�ǵ�һ�㣬������alpha-betaһ��
 * ��һ����Ҫ������һ���߷����޳��ذܵ㣬ͬʱ��һ�㲻��Ҫbeta�����Ͻ磬Խ��Խ�� */
int pvs(Tree head, int depth) {
    Tree p;
    Line buf[LENGTH];
    int i, j, v;
    int alpha = N_INFINITY;
    int found_PV = 0;
    int shape_buf[4];

    buf_move_board(buf);
    for (p = head; p->point_score != NULL_SCORE; p++) {
        /* �����ذܵ� */
        if (p->point_score == LOSE_SCORE)
            continue;
        i = p->i;
        j = p->j;
        set_bit_board(i, j);
        set_point(p, shape_buf);
        if (found_PV) {
            v = -alpha_beta(p, buf, g_move, depth - 1, -alpha - 1, -alpha);
            if (v > alpha)
                v = -alpha_beta(p, buf, g_move, depth - 1, N_INFINITY, -alpha);
        } else 
            v = -alpha_beta(p, buf, g_move, depth - 1, N_INFINITY, -alpha);

        if (v > alpha) {
            PV_p = p;
            found_PV = 1;
            alpha = v;
            next_score[0] = now_score[0];
            next_score[1] = now_score[1];
        }
        /* �޳��ذܵ� */
        if (v <= -100000)
            p->point_score = LOSE_SCORE;

        reset_point(p, shape_buf);
        re_move_board(j ,buf);
    }

    return alpha;
}

void AI_op() {
    clock_t start_t, end_t;
    Tree head, p;
    int val, now_depth;

    start_t = clock();
    generate_time = sort_time = 0;

    head = get_move(g_i, g_j, 0, g_move_buf, g_move);

    free(g_move);
    g_move = head;

    if (now_score[bool_player^1] > 2000)
        kill_cut(head);
    else 
        common_cut(head);

    /*
     *�Ƚ��д��10-15����ɱ������ʧ�ܾͽ���8��PVS����
     *��ɱ�����ڵ��Сbug���ύ����ʱ����
    */

    // if (alpha_beta_kill(PV_p, g_move_buf, g_move, 10, N_INFINITY, P_INFINITY) < 200000) {
        // printf("ʧ��");
    /* �������� 
     * �������������ǳ����޳��ذܵ㣬�����������ٶȣ�
     * ͬʱ�ҵ����Ӯ����������ͨ��ǳ����Ϣ�Խڵ����򣬱��������������˵����������ʷ�����򣬺���������*/  
    for (now_depth = 1; now_depth <= MAXDEPTH; now_depth += 1) {
        val = pvs(head, now_depth);
        if (val >= 100000)
            break;
    }
    // } else  
    //     printf("�ɹ�");
    end_t = clock();
    now_score[0] = next_score[0];
    now_score[1] = next_score[1];
    board_shape[0][PV_p->j] = PV_p->shape[0]; 
    board_shape[1][PV_p->i] = PV_p->shape[1]; 
    board_shape[2][PV_p->left] = PV_p->shape[2]; 
    board_shape[3][PV_p->right] = PV_p->shape[3]; 
    g_i = PV_p->i;
    g_j = PV_p->j;
    system("cls");
    printf("��ǰ����� �ڣ�%d �ף�%d\n", now_score[0], now_score[1]);
    printf("����ʱ%.2fs\n", (end_t - start_t)/1000.0);
    printf("�����߷�ʱ��%d\n", generate_time);
    printf("����ʱ��%d\n", sort_time);
    printf("�ڵ���Ŀ%d\n", node_num);
    node_num = 0;
}

/* �������
 * �������õ�ڻ���3����������Ϣ���޸�����*/  
void set_point(Tree p, int *buf) {
    int i = p->i;
    int j = p->j;
    int num, index;
    buf[0] = board_shape[0][j];
    buf[1] = board_shape[1][i];
    buf[2] = board_shape[2][p->left];
    buf[3] = board_shape[3][p->right];
    for (index = 0; index < 4; index++) {
        /* ����С��5û��Ҫ���� */
        if((num = get_line_num(i, j, index)) < 5) 
            continue;
        now_score[0] -= score_table[0][num][buf[index]];
        now_score[0] += score_table[0][num][p->shape[index]];
        now_score[1] -= score_table[1][num][buf[index]];
        now_score[1] += score_table[1][num][p->shape[index]];
    }
    board_shape[0][j] = p->shape[0]; 
    board_shape[1][i] = p->shape[1]; 
    board_shape[2][p->left] = p->shape[2]; 
    board_shape[3][p->right] = p->shape[3]; 
    renju[i][j] = player;
    bit_board[j] &= bit_set[i];
    CHANGE_PLAYER;
}

/* �������
 * �����̹���ڻָ�3����������Ϣ�ۻָ�����*/  
void reset_point(Tree p, int *buf) {
    int i = p->i;
    int j = p->j;
    int num, index;
    CHANGE_PLAYER;
    renju[i][j] = 0;
    bit_board[j] |= ~bit_set[i];
    board_shape[0][j] = buf[0]; 
    board_shape[1][i] = buf[1]; 
    board_shape[2][p->left] = buf[2]; 
    board_shape[3][p->right] = buf[3]; 
    for (index = 0; index < 4; index++) {
        if((num = get_line_num(i, j, index)) < 5) 
            continue;
        now_score[0] += score_table[0][num][buf[index]];
        now_score[0] -= score_table[0][num][p->shape[index]];
        now_score[1] += score_table[1][num][buf[index]];
        now_score[1] -= score_table[1][num][p->shape[index]];
    }
}

/* 
 * �������ϳ��ֻ��������ġ�����ʱ����Ҫ�ü�һЩ��Ȼ�����ܵ��߷� 
 * ��ʵ�ϵ��������ʱֻ�з�ºͳ��ĳ��壬�Է����Ļ���ʱֻ�з�»��߳��壬
 * ���Ǳ������Ὣ�Է��ܳɻ����ĵ�Ҳ������������ô����
 */  
int kill_cut(Tree head) {
    Tree p;
    for (p = head; p->j != NULLPOSITION && (p->point_score > 1800); p++);
    p->point_score = NULL_SCORE;
    if (p - head > 0)
        return 1;
    else
        return 0;
}

/*  ������ƽ��ʱ��ѡǰ��ʮ�ִ���߷�*/  
void common_cut(Tree head) {
    for (int index = 0; head->j != NULLPOSITION && index != 20; head++, index++);
    head->point_score = NULL_SCORE;
}

/*�򵥵Ŀ���*/
void quick_sort(Tree move_set, int left, int right) {
    int i, j, std;

     if (left > right)
        return;
   
    i = left;
    j = right;
    std = move_set[left].point_score;

    while (i != j) {
        while (move_set[j].point_score <= std && j > i)
            j--;
        while (move_set[i].point_score >= std && j > i)
            i++;
        
        if (j > i) 
            exchange(move_set, i, j);
    }
    exchange(move_set, i, left);

    quick_sort(move_set, left, i - 1);
    quick_sort(move_set, i + 1, right);
}

/*��������Node��Ԫ��*/
void exchange(Tree move_set, int i, int j) {
    Node temp;
    temp = move_set[i];
    move_set[i] = move_set[j];
    move_set[j] = temp;
}

//����Ϊ��ɱ��������������ͨalpha-beta���ƣ�����ÿ��ֻ�������壬Ŀǰ�е�Сbug���������½����ύ�治��

// int alpha_beta_kill(Tree pNode, Line* last_buf, Tree last_move, int depth, int alpha, int beta) {
//     Tree p, head;
//     Line buf[LENGTH];
//     int v, score;
//     int found_PV = 0;
//     int best = N_INFINITY;
//     int i = pNode->i, j = pNode->j;
//     int shape_buf[4];

//     // �÷ֹ��ߵ�������жϽ���
//     if (player == WHITE && pNode->point_score > 3600) { 
//         if (forbid(i, j))
//             return P_INFINITY;
//         else
//             renju[i][j] = BLACK;
//     }

//     //���ж���û���Ѿ�����
//     if (win(i, j)) 
//         return N_INFINITY;

//     //���������ľ�
//     if (depth <= 0){
//         if(player == BLACK) 
//             return now_score[0] - now_score[1];   
//         else 
//             return now_score[1] - now_score[0];   
//     }
//     //��ȡ�߷�
//     head = get_move_kill(i, j, depth, last_buf, last_move);
//     if (!kill_cut(head)) {
//         free(head);
//         head = NULL;
//         if(player == BLACK) 
//             return now_score[0] - now_score[1];   
//         else 
//             return now_score[1] - now_score[0];  
//     }
//     buf_move_board(buf);

//     for (p = head; p->point_score != NULL_SCORE; p++) {
//         node_num++;
//         i = p->i;
//         j = p->j;

//         set_bit_board(i ,j);
//         set_point(p, shape_buf);
//         //����ҵ�PV�߷� �ü�С����
//         if (found_PV) {
//             v = -alpha_beta_kill(p, buf, head, depth - 1, -alpha - 1, -alpha);
//             if (v > alpha && v < beta)
//                 v = -alpha_beta_kill(p, buf, head, depth - 1, -beta, -alpha);
//         } else 
//             v = -alpha_beta_kill(p, buf, head, depth - 1, -beta, -alpha);
//         reset_point(p, shape_buf);
//         re_move_board(j, buf);
//         if (v > best) {
//             best = v;
//             if (v > alpha)
//                 alpha = v;
//             if (depth == KILL_DEPTH)
//                 PV_p = p;
//             if (v >= beta)
//                 break;
//         }
//     }
//     free(head);
//     head = NULL;

//     return best;
// }
