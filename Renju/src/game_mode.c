#include "./game_mode.h"
 
/* ������Ϸģʽ��� */
 
int player = 1;         //1Ϊ��2Ϊ��
int bool_player = 0;    //0Ϊ��1Ϊ��
Tree g_move = NULL;     //ָ����һ���߷��������߷�ʱ��
int g_i = 7;            
int g_j = 7;            //�����浱ǰ�ⲽҪ�ߵ�λ��

/*���˶�ս*/
void PvsP() {
    int result;

    system("cls");
    set_board();
    while (!(result = win(g_i, g_j)) && !is_full()) {
        printf("�����ʽΪ(h8)��(H8)\n");
        set();
        system("cls");
        set_board();
        print_pos();
        CHANGE_PLAYER;
    }
    judge_result(result);
}

void PvsAI() {
	int result;
	int time_AI = 0;
    char player_color;

    /*��ʼ��AI��صĹ�ϣ��֮��Ķ���*/
    printf("����ing\n"); 
	init_hash();        //���ֱ�
	init_bit_board();   //λ����
	init_move_table();  //�߷���

    while (getchar() != '\n')
        ;	
    printf("ѡ����ҳַ�����������(1)���������(2):");
    player_color = getchar();
	while ( !isdigit(player_color) || ((player_color -= '0') != 1 && player_color != 2)) {
		printf("�����������������");
		while (getchar() != '\n')
			;	
		player_color = getchar();
	}

    /*ѡ���������Ԫ����*/
    if (player_color == WHITE) {
        new_set(g_i, g_j);
        board_shape[0][7] = 2187; //2187������������10000000
        board_shape[1][7] = 2187; 
        board_shape[2][14] = 2187; 
        board_shape[3][14] = 2187; 
        set_board();
        print_pos();
        CHANGE_PLAYER;
    } else 
        set_board();

	while (!(result = win(g_i, g_j)) && !is_full()) {
		if (player == player_color) {
			player_set();
            system("cls");
        }
		else 
			AI_set();
        // system("cls");
        set_board();
        print_pos();
		CHANGE_PLAYER;
	}
	free(g_move);
	g_move = NULL;
	set_board();
    judge_result(result);
}

//������ս���ڲ���AI
void AIvsAI() {
	int result, step;
	int time_b, time_w;
	clock_t start_t, end_t;

    step = time_b = time_w = 0;

	printf("����ing\n"); 
    init_hash();
	init_bit_board();   //λ����
	init_move_table();  //�߷���

    renju[g_i][g_j] = player + 2;
    bit_board[g_j] &= bit_set[g_i];
    set_bit_board(g_i, g_j);
    board_shape[0][7] = 2187; 
    board_shape[1][7] = 2187; 
    board_shape[2][14] = 2187; 
    board_shape[3][14] = 2187; 

	set_board();
    print_pos();
    CHANGE_PLAYER;

	while (!(result = win(g_i, g_j)) && !is_full()) {
        start_t = clock();
        AI_set();
        end_t = clock();
        CHANGE_PLAYER;
        set_board();
    }
	free(g_move);
	g_move = NULL;
	set_board();
}

void print_pos() {
    if (player == WHITE) 
        printf("����������%c%dλ��\n", g_j + 'a', g_i + 1);
    else 
        printf("����������%c%d\n", g_j + 'a', g_i + 1);
}

