#ifndef _ZOBRIST_H_
#define _ZOBRIST_H_

#include "../include/common.h"

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

void init_rand();    //��ʼ�������
table* init_table(); //��ʼ���û���
int TT_search(int depth); //���
void TT_insert(int point, int depth); //��������
int zobrist_hash(unsigned long long key); //�Ե�ǰkeyȡindex
void free_all(); //�ͷŹ�ϣ���ڴ�

#endif