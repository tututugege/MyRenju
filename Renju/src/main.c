#include "../include/set.h"

extern int player_i;
extern int player_j;
int player_i = 0;
int player_j = 0;
int player = 1;
int fir[LENGTH][LENGTH] = {0};
unsigned long long now_key = 0;
unsigned long long zobrist[LENGTH][LENGTH][2] = {0};

void init_rand();
void init_point_table();
void set_board(); //��ӡ��ǰ���Ƶ�����
void set();      //���� 
void AI_set();    //AI����

int main() {
	int result, step, i, j;
	int time_b, time_w;
	clock_t start_t, end_t;

	init_rand();
	init_point_table();

	step = time_b = time_w = 0;
	AI_i = AI_j = 7;
	fir[7][7] = player + 2;

	change_player();
	set_board();

	while (!(result = win(AI_i, AI_j)) && !is_full()) {
		if (player == BLACK) {
			start_t = clock();
			AI_set();
			now_key ^= zobrist[AI_i][AI_j][BLACK - 1];
			end_t = clock();
			time_b += end_t - start_t;
			step++;
		} else {
			start_t = clock();
			AI_set();
			now_key ^= zobrist[AI_i][AI_j][WHITE - 1];
			end_t = clock();
			time_w += end_t - start_t;
			step++;
		}
		change_player();
		set_board();
	}
	set_board();
	if (result == BLACK) {
		printf("����Ӯ\n");
	}
	else if(result == WHITE) {
		printf("����Ӯ\n");
	}
	printf("����ƽ������ʱ��%d\n����ƽ������ʱ��%d\n�ܲ���%d\n", time_b/(step/2), time_w/(step/2), step);
	system("pause");
}

void init_rand() {
    int i, j, k;
    srand((unsigned int)time(NULL));

	for (k = 0; k < 2; k++) {
		for (i = 0; i < LENGTH; i++) {
			for (j = 0; j < LENGTH; j++) {
				for(k = 0; k < 63; k++) {
					zobrist[i][j][0] += rand() & 0b1;
					zobrist[i][j][0] = zobrist[i][j][0] << 1;
				}
				zobrist[i][j][0] += rand() & 0b1;
			}
		}
	}
}