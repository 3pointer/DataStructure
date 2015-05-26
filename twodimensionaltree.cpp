/*************************************************************************
	> File Name: poj21552.cpp
	> Author: 3pointer
	> Mail: 
	> Created Time: 2015年05月26日 星期二 17时24分21秒
 ************************************************************************/
//poj 2155

#include<iostream>
#include<stdio.h>
#include <string.h>
#define N 1101
using namespace std;

int k[N][N];
int n;

int lowbit(int x){
    return x&(-x);
}

void update(int x, int y){
    for(int i = x; i <= n; i += lowbit(i)){
        for (int j = y; j <= n; j += lowbit(j)){
            k[i][j] ++;
        }
    }
}

int getsum(int x, int y){
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i)){
        for (int j = y; j > 0; j -= lowbit(j)){
            sum += k[i][j];
        }
    }
    return sum;
}

int main(){
    int q;
    int t;
    int a, b, c, d;
    char ch[3];
    scanf("%d", &t);
    while(t --){ 
    	memset(k, 0, sizeof(k));
        scanf("%d%d", &n, &q);
        while(q --){
            scanf("%s%d%d", ch, &a, &b);
            if (ch[0] == 'C'){
                scanf("%d%d", &c, &d);
                update(a, b);
                update(c + 1, b);
                update(a, d + 1);
                update(c + 1, d + 1);
            } else {
                printf("%d\n", getsum(a, b) & 1);
            }
        }
        printf("\n");
    }
    return 0;
}


