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

typedef struct hash_item {
	unsigned long long key;
	int point;    //����ֵ
	char depth;	  //�ڵ����
} item;

typedef struct hash_table {
	item *data;
} table;
