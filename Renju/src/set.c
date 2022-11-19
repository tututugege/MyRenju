#include "../include/set.h"
//���̻�������
//��ӡ���� ���� �ж���Ӯ

void AI_operation();//���⿪ʼ����AI
void set_board();   //��ӡ��ǰ���Ƶ�����
void set();          //���� 
void AI_set();       //AI����
void print_piece(int i, int j);
void get_input();

extern int player_i;
extern int player_j;

/*���д�ӡ����*/
void set_board() { 
    int i, j;
    //���϶��´�ӡ�����i��LENGTH-1��ʼ�ݼ�
    //ÿ�е�һ�����ŷ����ֱ߿��������������������⴦��
    for (i = LENGTH - 1; i >= 0; i--) {    
        printf("%2d", i + 1);               //��ӡ�б�
        if (fir[i][0] == 0) {
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
            if (fir[i][j] == 0) {
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
        if (fir[i][LENGTH - 1] == 0) {
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
    if (fir[i][j] == BLACK) printf("��");
    else if (fir[i][j] == WHITE) printf("��");
    else if (fir[i][j] == LASTBLACK) {
        printf("��");
        fir[i][j] = BLACK;
    }
    else {
        printf("��");
        fir[i][0] = WHITE;
    }
}

void set() {
    get_input();
    fir[player_i][player_j] = player + 2;
    now_key = now_key ^ zobrist[player][player_j][player - 1];

    if (player == WHITE) printf("����������%c%dλ��\n", player_j + 'a', player_i + 1);
    else printf("����������%c%d\n", player_j + 'a', player_i + 1);
}

void AI_set() {
    AI_operation();
    fir[AI_i][AI_j] = player + 2;
    now_key ^= zobrist[AI_i][AI_j][player - 1];

    if (player == WHITE) printf("����(AI)������%c%dλ��\n", AI_j + 'a', AI_i + 1);
    else printf("����(AI)������%c%d\n", AI_j + 'a', AI_i + 1);
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
    do { //������λ���������ڲ��Ҹ�λ����������right_inputΪ1 ����Ϊ0һֱѭ��
        //ֱ��������ĸ�������ڷ�Χ�ڲ��ܳ�ѭ��
        while (getchar() != '\n')
            ;   //�����������ж������� ��ͬ
        scanf("\n%c%d", &player_j, &player_i);  //\n���ղ����Ļس��� ��ͬ
        while (((player_j < 'a' || player_j > 'o') && (player_j <'A' || player_j >'O')) || (player_i <= 0 || player_i > LENGTH)) { 
            printf("�����ַ��Ƿ�������������\n");
            while (getchar() != '\n')
                ;  
            scanf("\n%c%d", &player_j, &player_i);  
        }
        player_j = (player_j >= 'a' && player_j <='o') ? player_j - 'a' : player_j - 'A';
        player_i--;
        //�ж�����λ���Ƿ��Ѿ�������
        if (fir[player_i][player_j] != 0) {
            printf("����λ�������ӣ����������� \n");
        } else if (player == WHITE || !forbid(player_i, player_j)) 
            right_input = 1;
    } while (right_input != 1);
}