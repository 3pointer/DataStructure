#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define N 200010

stack<int>s;
int ans[N];
int a[N];

struct node
{
    int l, r, k;
    int s;
    bool operator < (const node & n) const{
        if (n.k == k){
            return s > n.s;
        }
        return k > n.k;
    }

}b[N];

int main(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    a[0] = -1;
    a[n + 1] = -1;

    s.push(0);
    for (int i = 1; i <= n; i ++){
        int x = s.top();
        while (a[x] >= a[i]){
            s.pop();
            x = s.top();
        }
        s.push(i);
        b[i].l = x + 1;
    }
    while(!s.empty())
        s.pop();
    s.push(n + 1);
    for (int i = n; i >= 1; i --){
        int x = s.top();
        while (a[x] >= a[i]){
            s.pop();
            x = s.top();
        }
        s.push(i);
        b[i].r = x - 1;
        //b[i].k = a[i];
        //b[i].s = b[i].r - b[i].l + 1;
    }
    //cool part
    for (int i = 1; i <= n; i ++){
        int len = b[i].r - b[i].l + 1;
        ans[len] = max(ans[len], a[i]);
    }
    for (int i = n - 1; i >= 1; i --){
        ans[i] = max(ans[i], ans[i + 1]);
    }
    for (int i = 1; i <= n; i ++){
        cout << ans[i] << " ";
    }
    /*
    int cou = 1;
    sort(b + 1, b + n + 1);    
    for (int i = 1; cou <= n;i ++){
        while (b[i].s >= cou){
            cout << b[i].k << " ";
            cou ++;
        }
    }
    */
    return 0;
}

