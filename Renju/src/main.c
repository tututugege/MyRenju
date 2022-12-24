/********************************************************************************
* @File name: tututuRenju
* @Author: Tututu(���ꈐ)
* @Date: 2022-12-24
* @Compiler: MinGW gcc
* @Description: UCAS c���Գ�����ƴ���ҵ����������������˶�ս���˻���ս�ͻ�����ս
				AI���ɲ���ΪPVS�������������alpha-beta����ʵ��Լ8������

********************************************************************************/
#include "../include/main.h"

int main() {
	system("color F0"); //������ɫΪ�׵׺���,���ۺÿ�
	char game_mode;
	printf("��������Ϸģʽ�����˶�ս(0) �˻���ս(1) ������ս(2)��");
	game_mode = getchar();
	while ( !isdigit(game_mode) || (game_mode -= '0') > 2) {
		printf("�����������������");
		while (getchar() != '\n')
			;	//���������
		game_mode = getchar();
	}

	/*������Ϸģʽ*/
	if (game_mode == 0)
		PvsP();
	else if (game_mode == 1)
		PvsAI();
	else 
		AIvsAI();

	system("pause");
}