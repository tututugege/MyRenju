#define MAXDEPTH 4   //�������
#define P_INFINITY 200000000
#define N_INFINITY -200000000
#define HASHSIZE 33554432 //�û����С
#define NULLKEY 33554432  
#define NULLPOSITION 225

typedef struct hash_item {
	unsigned long long key;
	int point;    //����ֵ
	char depth;	  //�ڵ����
} item;

typedef struct hash_table {
	item *data;
} table;

typedef struct move_head {
	tree move_head;
	struct move_head* next;
} move_head_node;
//�����¼��������Ľڵ��ַ ��������������free 

extern table* tt; //�û���
extern int AI_i;
extern int AI_j;

tree get_memory(); //�����ڴ�
void free_all(); //�ͷ��ڴ�
tree get_move(int parent_pointd, int depth); 			//��ȡ�ŷ�                   
int move_evaluate(int i, int j, int depth);	 			//�ŷ�����
int alpha_beta(tree pNode, int depth, int alpha, int beta); //fail-soft + PVS + ���Ųü�
tree sort(tree p_head, tree p_end);						//��������(�鲢����)
tree merge(tree left, tree right);
void resort(tree p, tree* p_first_child);
										
table* init_table(); //��ʼ���û���
int TT_search(int depth); //���
void TT_insert(int point, int depth); //��������
int zobrist_hash(unsigned long long key); //�Ե�ǰkeyȡindex