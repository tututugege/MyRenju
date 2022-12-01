#include "../include/game_mode.h"

int player = 1;
table* tt = NULL;
Tree g_move = NULL;
int g_i = 7;
int g_j = 7;

void PvsP() {
    int result;

    system("cls");
    set_board();
    while (!(result = win(g_i, g_j)) && !is_full()) {
        printf("�����ʽ(h8)��(H8)\n");
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

    //��ʼ��AI��صĹ�ϣ��֮��Ķ���
	init_rand(); //�����
	init_point_table(); //���ֱ�
	init_bit_board();   //λ����
	init_move_table();  //�߷���

    while (getchar() != '\n')
        ;	
    printf("ѡ�񣺺�������(1)���������(2):");
    player_color = getchar();
	while ( !isdigit(player_color) || ((player_color -= '0') != 1 && player_color != 2)) {
		printf("�����������������");
		while (getchar() != '\n')
			;	
		player_color = getchar();
	}

    //ѡ���������Ԫ����
    if (player_color == WHITE) {
        new_set(g_i, g_j);
        set_board();
        print_pos();
        CHANGE_PLAYER;
    } else 
        set_board();

	while (!(result = win(g_i, g_j)) && !is_full()) {
        //��ʼ���û���
		tt = init_table();
		if (player == player_color) 
			player_set();
		else 
			AI_set();
        system("cls");
        set_board();
        print_pos();
		CHANGE_PLAYER;
        TT_free();
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

	init_rand(); //�����
	init_point_table(); //���ֱ�
	init_bit_board();   //λ����
	init_move_table();  //�߷���

    renju[g_i][g_j] = player + 2;
    now_key ^= zobrist[g_i][g_j][BLACK];

    set_bit_board(g_i, g_j);
	set_board();
    print_pos();
    CHANGE_PLAYER;

	while (!(result = win(g_i, g_j)) && !is_full()) {
		tt = init_table();
        start_t = clock();
        AI_set();
        end_t = clock();
        if (player == BLACK) {
            time_b += end_t - start_t;
        } else {
            time_w += end_t - start_t;
        }
        step++;
        CHANGE_PLAYER;
        set_board();
        TT_free();
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

