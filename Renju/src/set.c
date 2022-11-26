#include "../include/set.h"
//���̻�������
//��ӡ���� ���� �ж���Ӯ

/*���д�ӡ����*/
void set_board() { 
    int i, j;
    //���϶��´�ӡ�����i��LENGTH-1��ʼ�ݼ�
    //ÿ�е�һ�����ŷ����ֱ߿��������������������⴦��
    for (i = LENGTH - 1; i >= 0; i--) {    
        printf("%2d", i + 1);               //��ӡ�б�
        if (fir[i][0] == EMPTY) {
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
            if (fir[i][j] == EMPTY) {
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
        if (fir[i][LENGTH - 1] == EMPTY) {
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

void print_piece(int i, int j) {
    switch (fir[i][j]) {
    case BLACK:
        printf("��");
        break;
    case WHITE:
        printf("��");
        break;
    case LASTBLACK:
        printf("��");
        fir[i][j] = BLACK;
        break;
    default:
        printf("��");
        fir[i][j] = WHITE;
        break;
    }
}

void set() {
    get_input();
    new_set(g_i, g_j);

    if (player == WHITE) 
        printf("����������%c%dλ��\n", g_j + 'a', g_i + 1);
    else 
        printf("����������%c%d\n", g_j + 'a', g_i + 1);
}

void AI_set() {
    AI_operation();
    new_set(g_i, g_j);

    if (player == WHITE) 
        printf("����(AI)������%c%dλ��\n", g_j + 'a', g_i + 1);
    else 
        printf("����(AI)������%c%d\n", g_j + 'a', g_i + 1);
}

int lineLength(int i, int j, int dx, int dy) {
    int k, l;
    int num = 1;
    int last_player = player % 2 + 1;
    for (k = i + dx, l = j + dy; within_range(k) && within_range(l) && fir[k][l] == last_player; k += dx, l += dy, num++);    
    for (k = i - dx, l = j - dy; within_range(k) && within_range(l) && fir[k][l] == last_player; k -= dx, l -= dy, num++);    

    return num;
} //���������Ŀ

//��������λ���ж��Ƿ��Ѿ�����
int win(int i, int j) {
    if (lineLength(i, j, 1, 0) >= 5 || lineLength(i, j, 1, 1) >= 5 || lineLength(i, j, 1, -1) >= 5 || lineLength(i, j, 0, 1) >= 5) {
        if (player == BLACK)
            return WHITE;
        else
            return BLACK;
    }
    else return 0;
}

//�ж�i�Ƿ���0-14��������
int within_range(int i) {
    if (i >= 0 && i < LENGTH) return 1;
    else return 0; 
}

//1��2 2��1
void change_player() {
    player ^= 0b11;
}

int is_full() {
    int i, j;

    for (i = 0; i < LENGTH; i++) {
        for (j = 0; j < LENGTH; j++) {
            if (fir[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void get_input() {
    int right_input = 0;
    char temp_j;
    do { 
        while (getchar() != '\n')
            ;   //���������
        scanf("\n%c%d", &temp_j, &g_i);  //\n���ղ����Ļس��� ��ͬ

        while (((temp_j < 'a' || temp_j > 'o') && (temp_j <'A' || temp_j >'O')) || (g_i <= 0 || g_i > LENGTH)) { 
            printf("�����ַ��Ƿ�������������\n");
            while (getchar() != '\n')
                ;  
            scanf("\n%c%d", &temp_j, &g_i);  
        }
        g_j = (temp_j >= 'a' && temp_j <='o') ? temp_j - 'a' : temp_j - 'A';
        g_i--;
        //�ж�����λ���Ƿ��Ѿ�������
        if (fir[g_i][g_j]) {
            printf("����λ�������ӣ����������� \n");
        } else if (player == WHITE || !forbid(g_i, g_j)) 
            right_input = 1;
    } while (right_input != 1);
}

void new_set(int i, int j) {
    fir[i][j] = player + 2;
    now_key ^= zobrist[i][j][player - 1];
    cache_move_board();
    set_bit_board(i, j);
}

