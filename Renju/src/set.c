#include "./set.h"

int renju[LENGTH][LENGTH] = {0}; //��������

/*���д�ӡ����*/
void set_board() { 
    int i, j;
    /*���϶��´�ӡ�����i��LENGTH-1��ʼ�ݼ�
     *ÿ�е�һ�����ŷ����ֱ߿��������������������⴦��*/
    for (i = LENGTH - 1; i >= 0; i--) {    
        printf("%2d", i + 1); //��ӡ�б�
        if (renju[i][0] == EMPTY) {
            if (i == LENGTH - 1) 
                printf("��");
            else if (i == 0) 
                printf("��");
            else 
                printf("��");
        } else 
            print_piece(i, 0);
        /*ÿ�еڶ������ŵ������ڶ������ſ�����������
         *ͬ����Ϊ���ֱ߿�����������������*/
        for (j = 1; j < LENGTH - 1; j++){   
            if (renju[i][j] == EMPTY) {
                if (i == LENGTH - 1) 
                    printf("��");
                else if (i == 0) 
                    printf("��");
                else 
                    printf("��");
            } else         
                print_piece(i, j);
        }
        //ÿ�����һ�����ŷ����ֱ߿�����������������
        if (renju[i][LENGTH - 1] == EMPTY) {
            if (i == LENGTH - 1) 
                printf("��");
            else if (i == 0) 
                printf("��");
            else 
                printf("��");
        } else 
            print_piece(i, LENGTH - 1);
        printf("\n");
    }
    printf("   ");
    //��ӡ�б�
    for (i = 'A'; i < 'A' + LENGTH; i++) printf("%c ", i);
    printf("\n\n");
}

/* ���������ӡ���� */
void print_piece(int i, int j) {
    switch (renju[i][j]) {
    case BLACK:
        printf("��");
        break;
    case WHITE:
        printf("��");
        break;
    case LASTBLACK:
        printf("��");
        renju[i][j] = BLACK;
        break;
    default:
        printf("��");
        renju[i][j] = WHITE;
        break;
    }
}

/* �˻���սʱ�˵Ĳ���,����������嶯̬ˢ�����õĲ��� */
void player_set() {
    Node pt;
    int index, num, line;
    player_op();
    get_input();
    new_set(g_i, g_j);
    pt.i = g_i;
    pt.j = g_j;
    pt.left = LEFT_I(g_i, g_j);
    pt.right = RIGHT_I(g_i, g_j);
    get_point_score(&pt);
    for (index = 0; index < 4; index++) {
        if((num = get_line_num(g_i, g_j, index)) < 5) 
            continue;
        line = transX[index](g_i, g_j);
        now_score[0] -= score_table[0][num][board_shape[index][line]];
        now_score[0] += score_table[0][num][pt.shape[index]];
        now_score[1] -= score_table[1][num][board_shape[index][line]];
        now_score[1] += score_table[1][num][pt.shape[index]];
    }
    board_shape[0][pt.j] = pt.shape[0]; 
    board_shape[1][pt.i] = pt.shape[1]; 
    board_shape[2][pt.left] = pt.shape[2]; 
    board_shape[3][pt.right] = pt.shape[3]; 
}

void AI_set() {
    AI_op();
    new_set(g_i, g_j);
}

/* ���˶�ս�򵥶�ȡ�����жϽ��־ͺ� */
void set() {
    get_input();
    renju[g_i][g_j] = player + 2;
}

/* ���ض�Ӧ�����ϵ������ */
int lineLength(int i, int j, int dx, int dy) {
    int k, l;
    int num = 1;
    int last_player = renju[i][j];

    if (!last_player)
        return 0;
    for (k = i + dx, l = j + dy; in_range(k, l) && renju[k][l] == last_player; k += dx, l += dy, num++);    
    for (k = i - dx, l = j - dy; in_range(k, l) && renju[k][l] == last_player; k -= dx, l -= dy, num++);    

    return num;
} 

/* ������� */
void get_input() {
    int correct_input = 0;
    char temp_j;
    do { 
        while (getchar() != '\n')
            ;   //���������
        scanf("\n%c%d", &temp_j, &g_i);  //\n���ղ����Ļس��� ��ͬ

        while ((!within_range(temp_j - 'a') && !within_range(temp_j - 'A')) || !within_range(--g_i)) { 
            printf("�����ַ��Ƿ�������������\n");
            while (getchar() != '\n')
                ;  
            scanf("\n%c%d", &temp_j, &g_i);  
        }
        g_j = (temp_j > 'Z') ? temp_j - 'a' : temp_j - 'A';
        //�ж�����λ���Ƿ��Ѿ�������
        if (renju[g_i][g_j]) 
            printf("����λ�������ӣ����������� \n");
        else if (player == WHITE || !forbid(g_i, g_j)) 
            correct_input = 1;
        else 
            printf("����λ��Ϊ����\n");
    } while (correct_input != 1);
}

/* ����һ�������Ҫ��bit���̽�����ز��� */
void new_set(int i, int j) {
    renju[i][j] = player + 2;
    bit_board[j] &= bit_set[i];
    buf_move_board(g_move_buf);
    set_bit_board(i, j);
}

/* ������� */
void judge_result(int result) {
	if (result == BLACK) 
		printf("����Ӯ\n");
	else if(result == WHITE) 
		printf("����Ӯ\n");
	else	
		printf("��������ƽ��\n");
}

int win(int i, int j) {
    if (lineLength(i, j, 1, 0) >= 5 || lineLength(i, j, 1, 1) >= 5 || lineLength(i, j, 1, -1) >= 5 || lineLength(i, j, 0, 1) >= 5) {
        if (player == BLACK)
            return WHITE;
        else
            return BLACK;
    }
    else return 0;
}