#include "../include/set.h"
//���̻�������
//��ӡ���� ���� �ж���Ӯ

void AI_operation();                            //ai����ķ�װ
void set_board(); //��ӡ��ǰ���Ƶ�����
int* set(int* position);      //���� 
int* AI_set(int* position);    //AI����

/*���д�ӡ����*/
void set_board() { 
    int i, j;


    //���϶��´�ӡ�����i��LENGTH-1��ʼ�ݼ�
    //ÿ�е�һ�����ŷ����ֱ߿��������������������⴦��
    for (i = LENGTH - 1; i >= 0; i--) {    
        printf("%2d", i + 1);               //��ӡ�б�
        if (fir[i][0] == 0) {
            if (i == LENGTH-1) printf("��");
            else if (i == 0) printf("��");
            else printf("��");
        } else if (fir[i][0] == BLACK) printf("��");
        else if (fir[i][0] == WHITE) printf("��");
        else if (fir[i][0] == LASTBLACK) {
            printf("��");
            fir[i][0] = BLACK;
        }
        else {
            printf("��");
            fir[i][0] = WHITE;
        }
        //ÿ�еڶ������ŵ������ڶ������ſ�����������
        //ͬ����Ϊ���ֱ߿�����������������
        for (j = 1; j < LENGTH - 1; j++){   
            if (fir[i][j] == 0) {
                if (i == LENGTH-1) printf("��");
                else if (i == 0) printf("��");
                else printf("��");
            } else if (fir[i][j] == BLACK) printf("��");
            else if (fir[i][j] == WHITE) printf("��");
            else if (fir[i][j] == LASTBLACK) {
                printf("��");
                fir[i][j] = BLACK;
            }
            else {
                printf("��");
                fir[i][j] = WHITE;
            }
        }
        //ÿ�����һ�����ŷ����ֱ߿�����������������
        if (fir[i][LENGTH - 1] == 0) {
            if (i == LENGTH-1) printf("��");
            else if (i == 0) printf("��");
            else printf("��");
        } else if (fir[i][LENGTH - 1] == BLACK) printf("��");
        else if (fir[i][LENGTH - 1] == WHITE) printf("��");
        else if (fir[i][LENGTH - 1] == LASTBLACK) {
            printf("��");
            fir[i][LENGTH -1] = BLACK;
        }
        else {
            printf("��");
            fir[i][LENGTH - 1] = WHITE;
        } //ÿ�����һ��

        printf("\n");
    }
    printf("   ");

    //��ӡ�б�
    for (i = 'A'; i < 'A' + LENGTH; i++) printf("%c ", i);
    printf("\n\n");
}

int* set(int* position) {
    int i, j;
    int right_input; //������ȷ�ı�־
    char temp_j;     //��ʱ����û��������ĸ

    right_input = 0;
    if (is_full()) {
        free(position);
        return NULL;
    }//�������򷵻�null������position�Ŀռ�

    //���̲�����ʼ���벢���������Ƿ�Ϸ�
    while ( getchar() != '\n' );   //�����������ж������� ��ͬ
    scanf("\n%c%d", &temp_j, &i);  //\n���ղ����Ļس��� ��ͬ
    i--;

    if (player == WHITE) {  
        while(right_input != 1) { //������λ���������ڲ��Ҹ�λ����������right_inputΪ1 ����Ϊ0һֱѭ��
            //ֱ��������ĸ�������ڷ�Χ�ڲ��ܳ�ѭ��
            while (((temp_j < 'a' || temp_j > 'o') && (temp_j <'A' || temp_j >'O')) || (i < 0 || i > 14)) { 
                printf("�����ַ��Ƿ�������������\n");

                while ( getchar() != '\n' );  
                scanf("\n%c%d", &temp_j, &i);  
                i--;
            }
            if (temp_j >= 'a' && temp_j <='o') j = (int)(temp_j - 'a');
            else j = (int)(temp_j - 'A');
            
            //�ж�����λ���Ƿ��Ѿ�������
            if (fir[i][j] != 0) {
                printf("����λ�������ӣ����������� \n");
                while ( getchar() != '\n' ); 
                scanf(" %c%d", &temp_j, &i);
                i--;
            }
            else right_input = 1;
        }
    } else { 
        while(right_input != 1) {
            while (((temp_j < 'a' || temp_j > 'o') && (temp_j <'A' || temp_j >'O')) || (i < 0 || i > 14)) { 
                printf("�����ַ��Ƿ�������������\n");

                while ( getchar() != '\n' );  
                scanf("\n%c%d", &temp_j, &i);  
                i--;
            }
            if (temp_j >= 'a' && temp_j <='o') j = (int)(temp_j - 'a');
            else j = (int)(temp_j - 'A');

            if (fir[i][j] != 0) {
                printf("����λ�������ӣ����������� \n");
                while ( getchar() != '\n' );  
                scanf("\n%c%d", &temp_j, &i);
                i--;

            //��������ڰ���Ҫ��һ���жϽ���
            } else if (forbid(i, j)) {
                printf("����λ��Ϊ����\n");
                while ( getchar() != '\n' ); 
                scanf("\n%c%d", &temp_j, &i);
                i--;
            }
            else right_input = 1;
        }
    }
    // system("cls");
    fir[i][j] = player + 2;
    now_key = now_key ^ zobrist[i][j][player - 1];
    position[0] = i;
    position[1] = j;

    if (player == WHITE) printf("����������%c%dλ��\n", j + 'a', i + 1);
    else printf("����������%c%d\n", j + 'a', i + 1);
    set_board();
    change_player();
    return position;
}

int* AI_set(int* position) {
    if (is_full()) {
        free(position);
        return NULL;    
    }//������

    AI_operation();
    fir[AI_i][AI_j] = player + 2;
    now_key ^= zobrist[AI_i][AI_j][player - 1];
    position[0] = AI_i;
    position[1] = AI_j;

    if (player == WHITE) printf("����(AI)������%c%dλ��\n", position[1] + 'a', position[0] + 1);
    else printf("����(AI)������%c%d\n", AI_j + 'a', AI_i + 1);
    set_board();

    change_player();
    return position;
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