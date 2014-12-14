#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 210000

struct node
{
    int a, b, id;
}q[N];

long long lowbit(int p)
{
    return (p&-p);
}
long long c[N * 3];
long long getsum(int p)
{
    long long sum = 0;
    while(p)
    {
        sum += c[p];
        p -= lowbit(p);
    }
    return sum;
}
int n, m, ncount, pre[N * 3];
long long val[N * 3], tmp[N * 3], ans[N];

void insert(int p, long long d)
{
    while(p <= n)
    {
        c[p] += d;
        p += lowbit(p);
    }
}

int search(long long key)
{
    int l = 0;
    int r = n - 1;
    int ans;
    int mid;
    while(l <= r)
    {
        mid = (l + r)>>1;
        if (tmp[mid] >= key)
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    return ans;
}

int cmp(struct node x, struct node y)
{
    return x.b < y.b;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &val[i]);  //
            c[i] = 0;
            pre[i] = 0;
            tmp[i] = val[i];
        }
        c[n] = pre[n] = 0;
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
        {
            q[i].id = i;
            scanf("%d%d", &q[i].a, &q[i].b);
        }
        sort(q, q + m, cmp);
        sort(tmp, tmp + n);
        ncount = 1;
        int p = 0;
        for (int i = 0; i < n; i++)
        {
            int index = search(val[i]);
            if (pre[index])
                insert(pre[index], -1);
            insert(i + 1, 1);
            pre[index] = i + 1;
            while(q[p].b == i + 1 && p < m)
            {
                ans[q[p].id] = getsum(i + 1) - getsum(q[p].a - 1);
                p++;
            }
        }
        for (int i = 0; i < m; i++)
            printf("%lld\n", ans[i]);
    }
    return 0;
}
