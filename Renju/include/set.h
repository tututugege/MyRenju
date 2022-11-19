#ifndef _SET_H_
#define _SET_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//������غ�
#define BLACK 1 	//����	
#define WHITE 2		//����
#define LASTBLACK 3 //���µĺ���
#define LASTWHITE 4 //���µİ���
#define LENGTH 15   //���̳���
//AI�㷨���
#define MAXDEPTH 5   //�������
#define P_INFINITY 200000000
#define N_INFINITY -200000000
#define HASHSIZE 33554432
#define NULLKEY 33554432
#define NULLPOSITION 225
#define BIT_0 0b111000000000000
#define BIT_1 0b111100000000000
#define BIT_2 0b111110000000000
#define BIT_3 0b011111000000000
#define BIT_4 0b001111100000000
#define BIT_5 0b000111110000000
#define BIT_6 0b000011111000000
#define BIT_7 0b000001111100000
#define BIT_8 0b000000111110000
#define BIT_9 0b000000011111000
#define BIT_10 0b000000001111100
#define BIT_11 0b000000000111110
#define BIT_12 0b000000000011111
#define BIT_13 0b000000000001111
#define BIT_14 0b000000000000111

#ifndef _TREE_
#define _TREE_
typedef struct Node {
	unsigned char position;	  //�ڵ��Ӧ�·�
	int point;
	int result_point;
	struct Node *bro; 
	struct Node *first_child;
} Node; //�������ڵ� �����ֵܱ�ʾ��

typedef Node *tree; //��
#endif

//��¼��������Ľڵ��ַ �����ͷ�
typedef struct head {
	tree head;
	struct head* next;
} head_node;

extern table* tt;
extern int player;    //��¼��ǰ��ֵ�������
extern int fir[LENGTH][LENGTH];   //������Ϊȫ�ֱ���
extern unsigned long long now_key; //��ǰ��ֵ
extern int base[9];   //��ϣƥ��Ȩֵ  ������
extern int AI_i;   
extern int AI_j;      //ai��������������
extern unsigned long long zobrist[LENGTH][LENGTH][2];   //�û���(transposition table, TT)
extern int node_num;
extern short bit_board[LENGTH];

int is_full();
void set_board(); //��ӡ��ǰ���Ƶ�����
int* set(int* position);      //���� 
int* AI_set(int* position);    //AI����
int win(int i, int j); //�ж���Ӯ
int within_range(int i); //��0-14��������
void change_player();  //����

tree get_move(int parent_pointd, int depth);                   //����ÿ��λ�õ�λ�÷֣����п���Ӯ������ĵ���ǰ ����������ÿ���˳�� �����֦
void init_point_table();
int init_evaluate(int* board);
int point_evaluate(int i, int j, int depth);						//�������ķ�װ����
int move_evaluate(int i, int j, int depth);						//�������ķ�װ����
int init_point_evaluate(int i, int j, int dx, int dy);
int alpha_beta(tree pNode, int depth, int alpha, int beta); //MINMAX�㷨+alpha��beta��֦
void AI_operation();                            //ai����ķ�װ
void set_point(int i, int j);
void reset_point(int i, int j);
tree get_memory();
void free_all();
tree sort(tree p_head, tree p_end);						//����������(�鲢����)
tree merge(tree left, tree right);


void get_rand();
table* init_table();
int TT_search(int depth);
void TT_insert(int point, int depth);
int zobrist_hash(unsigned long long key);
void resort(tree p, tree first_child);

#endif