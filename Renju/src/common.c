#include "../include/common.h"

/*�ж�i�Ƿ���0-14��������*/
int within_range(int i) {
    if (i >= 0 && i < LENGTH) 
        return 1;
    else 
        return 0; 
}

/*�ж�i, j�Ƿ���0-14��������*/
int in_range(int i, int j) {
    if (within_range(i) && within_range (j))
        return 1;
    else
        return 0;
}

/* �ж������Ƿ��� */
int is_full() {
    int i, j;

    for (i = 0; i < LENGTH; i++) {
        for (j = 0; j < LENGTH; j++) {
            if (!renju[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}