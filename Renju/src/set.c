#include "../include/set.h"

int renju[LENGTH][LENGTH] = {0};

//���̻�������
//��ӡ���� ���� �ж���Ӯ

/*���д�ӡ����*/
void set_board() { 
    int i, j;
    //���϶��´�ӡ�����i��LENGTH-1��ʼ�ݼ�
    //ÿ�е�һ�����ŷ����ֱ߿��������������������⴦��
    for (i = LENGTH - 1; i >= 0; i--) {    
        printf("%2d", i + 1);               //��ӡ�б�
        if (renju[i][0] == EMPTY) {
            if (i == LENGTH - 1) 
                printf("��");
            else if (i == 0) 
                printf("��");
            else 
                printf("��");
        } else 
            print_piece(i, 0);
       //ÿ�еڶ������ŵ������ڶ������ſ�����������
        //ͬ����Ϊ���ֱ߿�����������������
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
            //ÿ�����һ��
        printf("\n");
    }
    printf("   ");
    //��ӡ�б�
    for (i = 'A'; i < 'A' + LENGTH; i++) printf("%c ", i);
    printf("\n\n");
}

//���������ӡ����
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

//�˻���սʱ�˵Ĳ���
void player_set() {
    Line buf[5];
    player_op();
    get_input();
    buf_bit_move(g_j, buf);
    g_score = move_evaluate(g_i, g_j, g_score, 0);
    printf("��ǰ����÷�%d\n", g_score);
    reset_point(g_i, g_j);
    re_bit_move(g_j ,buf);
    new_set(g_i, g_j);
}

void AI_set() {
    AI_op();
    new_set(g_i, g_j);
}

void set() {
    get_input();
    renju[g_i][g_j] = player + 2;
}

int lineLength(int i, int j, int dx, int dy) {
    int k, l;
    int num = 1;
    int last_player = player % 2 + 1;
    for (k = i + dx, l = j + dy; in_range(k, l) && renju[k][l] == last_player; k += dx, l += dy, num++);    
    for (k = i - dx, l = j - dy; in_range(k, l) && renju[k][l] == last_player; k -= dx, l -= dy, num++);    

    return num;
} //���������Ŀ

//��������λ���ж��Ƿ��Ѿ�����


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

void new_set(int i, int j) {
    renju[i][j] = player + 2;
    now_key ^= zobrist[i][j][player - 1];
    cache_move_board();
    set_bit_board(i, j);
}

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