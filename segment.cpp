/*************************************************************************
	> File Name: segment.cpp
	> Author: 3pointer
	> Mail: 
	> Created Time: 2015年05月25日 星期一 14时29分24秒
 ************************************************************************/
 //tyvj 1491

#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define N 100010
#define lson l, mid, s << 1
#define rson mid + 1, r, s << 1 | 1

int tree[N << 2];
int add[N << 2];

int n;

void pushup(int s){
    
}

void pushdown(int s){
    if (add[s]){
        tree[s << 1] += add[s];
        tree[s << 1 | 1] += add[s];
        add[s << 1] += add[s];
        add[s << 1 | 1] += add[s];
        add[s] = 0;
    }
}

void build(int l, int r, int s){
    tree[s] = 0;
    add[s] = 0;
    if (l == r){
        return ;
    }
    int mid = (l + r) >> 1;
    build(lson);
    build(rson);
}


void update(int ll, int rr, int l, int r, int s){
    if (ll <= l && r <= rr){
        tree[s] += 1;
        add[s] += 1;
        return;
    }
    pushdown(s);
    int mid = (l + r) >> 1;
    if (ll <= mid)
        update(ll, rr, lson);
    if (rr > mid)
        update(ll, rr, rson);
}

int query(int p, int l, int r, int s){
    if (l == r){
        return tree[s];
    }
    pushdown(s);
    int mid = (l + r) >> 1;
    if (p <= mid){
        return query(p, lson);
    } else {
        return query(p, rson);
    }
}
int main(){
    int p;
    int x, a, b;
    while(scanf("%d", &n) != EOF){
        build(1, n, 1);
        scanf("%d", &p);
        while(p --){
            scanf("%d", &x);
            if (x == 1){
                scanf("%d%d", &a, &b);
                update(a, b, 1, n, 1);
            } else {
                scanf("%d", &a);
                printf("%d\n", query(a, 1, n, 1) % 2);
            }
        }

    }

    return 0;
}
