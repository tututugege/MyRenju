#define MAXDEPTH 4   //�������
#define P_INFINITY 200000000
#define N_INFINITY -200000000
#define HASHSIZE 33554432
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
//��¼��������Ľڵ��ַ �����ͷ�
typedef struct head {
	tree head;
	struct head* next;
} head_node;

extern table* tt;

tree get_move(int parent_pointd, int depth);                   //����ÿ��λ�õ�λ�÷֣����п���Ӯ������ĵ���ǰ ����������ÿ���˳�� �����֦

int init_evaluate(int* board);
int point_evaluate(int i, int j, int depth);						//�������ķ�װ����
int move_evaluate(int i, int j, int depth);						//�������ķ�װ����
int init_point_evaluate(int i, int j, int dx, int dy);

int alpha_beta(tree pNode, int depth, int alpha, int beta); //MINMAX�㷨+alpha��beta��֦

tree get_memory();
void free_all();

tree sort(tree p_head, tree p_end);						//����������(�鲢����)
tree merge(tree left, tree right);
void resort(tree p, tree first_child);

table* init_table();
int TT_search(int depth);
void TT_insert(int point, int depth);
int zobrist_hash(unsigned long long key);