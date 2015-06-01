#include <stdio.h>
#include<string.h>
#define N 111
#define M 10001
#define INF 0x3f3f3f3f
#define min(a,b) a<b?a:b
using namespace std;
int nn;
double map[12][1200];
struct node{
    int to, cap, next;
    double w;

}e[M];
int ek;
int head[N];
int vis[N];
int link[N];


void init(){
    ek = 0;
    memset(head, -1, sizeof(head));

}

void addedge(int a, int b, double c, int d){
    e[ek].to = b;
    e[ek].w = c;
    e[ek].next = head[a];
    e[ek].cap = d;
    head[a] = ek++;

    e[ek].to = a;
    e[ek].w = -c;
    e[ek].next = head[b];
    e[ek].cap = 0;
    head[b] = ek++;

}
bool dfs(int v){
    for (int i = head[v]; i != -1; i = e[i].next){
        if (!vis[e[i].to]){
            vis[e[i].to] = 1;
            if (link[e[i].to] == -1 || dfs(link[e[i].to])){
                link[e[i].to] = v;
                return 1;
            }
        }
    }
    return 0;
}
int hungary(){
    int tot = 0;
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= nn; i++){
        memset(vis, 0, sizeof(vis));
        if (dfs(i))
            tot++;
    }
}
