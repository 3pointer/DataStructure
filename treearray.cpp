/*************************************************************************
	> File Name: treearray.cpp
	> Author: 3pointer
	> Mail: 
	> Created Time: 2015年05月25日 星期一 16时48分46秒
 ************************************************************************/
 //tyvj1491

#include<iostream>
#include<stdio.h>

#define N 100100
using namespace std;

int n;
int tree[N << 2];
int lowbit(int x){
    return x&(-x);
}

void update(int x){
    for (int i = x; i <= n; i += lowbit(i)){
        tree[i] += 1;
    }
}

int query(int x){
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i)){
        sum += tree[i];
    }
    return sum;
}

int main(){
    int p;
    int x, a, b;
    scanf("%d", &n);
    scanf("%d", &p);
    while(p --){
        scanf("%d", &x);
        if (x == 1){
            scanf("%d %d", &a, &b); 
            update(a);
            update(b + 1);
        } else {
            scanf("%d", &a);
            printf("%d\n", query(a) % 2);
        }
    }


    return 0;
}



