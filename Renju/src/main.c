#include "../include/main.h"

int main() {
	char game_mode;

	printf("��������Ϸģʽ�����˶�ս(0) �˻���ս(1) ������ս(2)��");
	game_mode = getchar();
	while ( !isdigit(game_mode) || (game_mode -= '0') > 2) {
		printf("�����������������");
		while (getchar() != '\n')
			;	
		game_mode = getchar();
	}

	if (game_mode == 0)
		PvsP();
	else if (game_mode == 1)
		PvsAI();
	else 
		AIvsAI();

	system("pause");
}