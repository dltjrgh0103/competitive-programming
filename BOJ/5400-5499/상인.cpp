#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500009;
const int INF = 0x3f3f3f3f;
typedef pair<int, int> pii;
typedef vector<pair<int, int> > vpi;
vpi mark[MAXN];
int n, u, d, s, uptree[2 * MAXN], downtree[2 * MAXN];
int query(int* arr, int l, int r)
{
    int ans = -INF;
    for (l += MAXN, r += MAXN; l <= r; l >>= 1, r >>= 1)
    {
        if (l & 1) ans = max(ans, arr[l++]);
        if (~r & 1) ans = max(ans, arr[r--]);
    }
    return ans;
}
void update(int* arr, int x, int v)
{
    x += MAXN;
    arr[x] = max(arr[x], v);
    for (; x > 1; x >>= 1) arr[x >> 1] = max(arr[x], arr[x ^ 1]);
}
void updatep(int x, int v)
{
    update(uptree, x, v - u * x);
    update(downtree, x, v + d * x);
}
int realquery(int a)
{
    return max(query(downtree, 0, a) - d * a, query(uptree, a, MAXN - 1) + u * a);
}
void markt(vpi& market)
{
    if (market.size() == 0) return;
    sort(market.begin(), market.end());
    vector<int> U, D;
    int sz = market.size();
    for (int i = 0; i < sz; i++)
    {
        int temp = realquery(market[i].first);
        U.push_back(temp), D.push_back(temp);
    }
    for (int i = 0; i < sz; i++)
    {
        if (i != 0) D[i] = max(D[i], D[i - 1] - d * (market[i].first - market[i - 1].first));
        D[i] += market[i].second;
    }
    for (int i = sz - 1; i >= 0; i--)
    {
        if (i != sz - 1) U[i] = max(U[i], U[i + 1] - u * (market[i + 1].first - market[i].first));
        U[i] += market[i].second;
    }
    for (int i = 0; i < sz; i++) updatep(market[i].first, max(U[i], D[i]));
}
int main()
{
    scanf("%d %d %d %d", &n, &u, &d, &s);
    for (int i = 0, x, y, z; i < n; i++)
    {
        scanf("%d %d %d", &x, &y, &z);
        mark[x].push_back(make_pair(y, z));
    }
    memset(uptree, 0xc0, sizeof(uptree));
    memset(downtree, 0xc0, sizeof(downtree));
    updatep(s, 0);
    for (int i = 1; i <= 500001; i++) markt(mark[i]);
    return !printf("%d", realquery(s));
}