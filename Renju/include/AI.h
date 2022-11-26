#ifndef _AI_H_
#define _AI_H

#define MAXDEPTH 4   //�������
#define P_INFINITY 200000000
#define N_INFINITY -200000000
#define HASHSIZE 33554432 //�û����С
#define NULLKEY 33554432  

typedef struct hash_item {
	unsigned long long key;
	int point;    //����ֵ
	char depth;	  //�ڵ����
} item;

typedef struct hash_table {
	item *data;
} table;


extern table* tt; //�û���
extern int AI_i;
extern int AI_j;

void free_all(); //�ͷ��ڴ�
tree get_move(unsigned short* last_buf, tree last_move, int i, int j); 			//��ȡ�ŷ�                   
void get_new_move(tree* move_set, int j, short line);
int move_evaluate(int i, int j, int depth);	 			//�ŷ�����
int alpha_beta(tree pNode, int last_point, unsigned short* last_buf, tree last_move, int depth, int alpha, int beta); //fail-soft + PVS + ���Ųü�
tree sort(tree p_head, tree p_end);						//��������(�鲢����)
// tree merge(tree left, tree right);
// unsigned short* buf_bit_move(int j);
// void resort(tree p, tree* p_first_child);
void buf_bit_move(int j, line* buf);
void reset_bit_move(int j, line* buf);
										
table* init_table(); //��ʼ���û���
int TT_search(int depth); //���
void TT_insert(int point, int depth); //��������
int zobrist_hash(unsigned long long key); //�Ե�ǰkeyȡindex

#endif