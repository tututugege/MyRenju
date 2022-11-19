#include "../include/set.h"
#include "../include/forbid.h"
//���ֺ���ʵ��

//�����ؼ�λ��Ϊ���߲���Ϊ����,������  ����
//���Ĺؼ�λ��Ϊ�м䲻���ǽ���(����)
int base[9] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561}; // ����λ(0) ����(1) ����(2) ���������Ƶ�012
                                                       // ���γ��ȹ̶�ʱ һ������Ψһȷ��һ������
int forbid(int i, int j) {

    fir[i][j] = BLACK;
    int num_four = 0;
    int num_three = 0;
    int max_length = 1;
    int line1 = lineLength(i, j, 1, 0);
    int line2 = lineLength(i, j, 0, 1);
    int line3 = lineLength(i, j, 1, 1);
    int line4 = lineLength(i, j, 1, -1);

    if (max_length < line1)
        max_length = line1;
    if (max_length < line2)
        max_length = line2;
    if (max_length < line3)
        max_length = line3;
    if (max_length < line4)
        max_length = line4;

    if (max_length > 5) {
        fir[i][j] = 0;
        if (line1 == 5 && line2 == 5 && line3 == 5 && line4 == 5) {
            return 0; //��򵥵ĳ������
        } else 
            return 1; 
    }

    if (isHuoFour(i, j, 1, 0)) num_four++;
    if (isHuoFour(i, j, 0, 1)) num_four++;
    if (isHuoFour(i, j, 1, 1)) num_four++;
    if (isHuoFour(i, j, 1, -1)) num_four++;

    //�жϻ���


    num_four += isChongFour(i, j, 1, 0) + isChongFour(i, j, 0, 1) + isChongFour(i, j, 1, 1) + isChongFour(i, j, 1, -1); 
    num_three += isHuoThree(i, j, 1, 0) + isHuoThree(i, j, 0, 1) + isHuoThree(i, j, 1, 1) + isHuoThree(i, j, 1, -1); 

    if (num_four >= 2 || num_three >= 2) {
        fir[i][j] = 0; 
        return 1;
    } else {
        fir[i][j] = 0;
        return 0;
    }
}

int isHuoFour(int i, int j, int dx, int dy) {
    int num;
    int now_i, now_j;
    int l_i, l_j, r_i, r_j;
    int l_edge = 1;
    int r_edge = 1;

    for (now_i = i, now_j = j, num = 0; fir[now_i][now_j] == BLACK && within_range(now_i) && within_range(now_j); now_i += dx, now_j += dy, num++);    

    if (now_i == LENGTH || now_j == -1 || now_j == LENGTH || fir[now_i][now_j] == WHITE) {
        l_edge = 0; //�ж�һ��
    } else {
        l_i = now_i;
        l_j = now_j;
    }

    for (now_i = i - dx, now_j = j - dy; within_range(now_i) && within_range(now_j) && fir[now_i][now_j] == BLACK; now_i -= dx, now_j -= dy, num++);    

    if (now_i == -1 || now_j == -1 || now_j == LENGTH || fir[now_i][now_j] == WHITE) {
        r_edge = 0; 
    } else {
        r_i = now_i;
        r_j = now_j;
    }

    if (num != 4 || (!l_edge && !r_edge)) return 0;

    if ((r_edge && !forbid(r_i, r_j)) || (l_edge && !forbid(l_i, l_j))) return 1;
    else return 0;
}

int isChongFour(int i, int j, int dx, int dy) {
    int value, key_i, key_j, now_i, now_j, search_i, search_j;
    int num = 0;
    int index1, index2;
    index2 = 0;

    for (now_i = i, now_j = j; index2 < 5 && within_range(now_i) && within_range(now_j); now_i -= dx, now_j -= dy, index2++) { 
        value = 0;
        search_i = now_i;
        search_j = now_j;
        for (index1 = 0; index1 < 5 && within_range(search_i) && within_range(search_j); index1++, search_i += dx, search_j += dy) {
            if (fir[search_i][search_j] == WHITE) 
                break;
            else 
                value += fir[search_i][search_j] * base[index1];
        } 
        if (index1 == 5) {
            if (value == chong_four_1) {
                key_i = now_i + 2*dx;
                key_j = now_j + 2*dy;
                if (!forbid(key_i, key_j)) num++;   //���Ľ��ֿ�����һ������ ��Ҫ�ۼ�
            } else if (value == chong_four_2) {
                key_i = now_i + 3*dx;
                key_j = now_j + 3*dy;
                if (!forbid(key_i, key_j)) num++;
            } else if (value == chong_four_3) {
                key_i = now_i + 1*dx;
                key_j = now_j + 1*dy;
                if (!forbid(key_i, key_j)) num++;
            }
        }
    }
    return num;
}

int isHuoThree(int i, int j, int dx, int dy) {
    int value, key_i, key_j, now_i, now_j, end_i, end_j, search_i, search_j;
    int index1; //��Ȩ�����ı��
    int index2 = 0; //��Ҫ��������ı��

    for (now_i = i - dx, now_j = j - dy; index2 < 4 && within_range(now_i) && within_range(now_j); now_i -= dx, now_j -= dy, index2++) {
        value = 0;
        search_i = now_i - dx;
        search_j = now_j - dy;
        if (within_range(search_i) && within_range(search_j) && fir[search_i][search_j] == BLACK) 
            continue; //�����к��� �����������޷����ɻ���

        search_i = now_i;
        search_j = now_j;
        for (index1 = 0; index1 < 6 && within_range(search_i) && within_range(search_j); index1++, search_i += dx, search_j += dy) {
            if (fir[search_i][search_j] == WHITE) break;
            else value += fir[search_i][search_j] * base[index1];
        } 

        end_i = now_i + index1*dx;
        end_j = now_j + index1*dy;

        if(index1 < 6) continue;
        else if(!within_range(end_i) || !within_range(end_j) || fir[end_i][end_j] != BLACK) {
            switch (value) {
                case huo_three1:
                    key_i = now_i + dx*1;  
                    key_j = now_j + dy*1;  
                    if (!forbid(key_i, key_j)) return 1;  //��������û��ͬһ�����ϵ���� ���ּ��ɷ���1
                    break;
                case huo_three2:
                    key_i = now_i + dx*4;  
                    key_j = now_j + dy*4;  
                    if (!forbid(key_i, key_j)) return 1;
                    break;
                case huo_three3:
                    key_i = now_i + dx*2;  
                    key_j = now_j + dy*2;  
                    if (!forbid(key_i, key_j)) return 1;
                    break;
                case huo_three4:
                    key_i = now_i + dx*3;  
                    key_j = now_j + dy*3;  
                    if (!forbid(key_i, key_j)) return 1; 
                    break;
            }
        } 
    }
    return 0;
}
    