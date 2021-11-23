#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
int n, m, k, q, d[111111], res[111111];
vector<vector<pair<int, int>>> vt;
set<int> st[111111];
int par[111111];
pair<int, pair<int, int>> edge[211111];
int find(int h) {
    return h == par[h] ? h : par[h] = find(par[h]);
}
void merge(int x, int y) {
    x = find(x);
    y = find(y);
    par[x] = y;
}
int main() {
    scanf("%d%d%d%d", &n, &m, &k, &q);
    vt.resize(n + 1);
    for (int i = 1; i <= n; i++)
        par[i] = i;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        vt[x].push_back({ y,z });
        vt[y].push_back({ x,z });
        edge[i].second = { x,y };
    }
    memset(d, -1, sizeof(d));
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        pq.push({ 0,x });
    }
    while (pq.size()) {
        int here = pq.top().second;
        int cost = -pq.top().first;
        pq.pop();
        if (d[here] != -1)continue;
        d[here] = cost;
        for (auto next : vt[here]) {
            if (d[next.first] == -1)
                pq.push({ -next.second - cost,next.first });
        }
    }
    for (int i = 1; i <= q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        st[x].insert(i);
        st[y].insert(i);
    }
    for (int i = 0; i < m; i++)
        edge[i].first = -min(d[edge[i].second.first], d[edge[i].second.second]);
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) {
        int lo = find(edge[i].second.first);
        int hi = find(edge[i].second.second);
        if (lo == hi)continue;
        if (st[lo].size() > st[hi].size())swap(lo, hi);
        for (auto next : st[lo]) {
            if (st[hi].count(next)) {
                res[next] = -edge[i].first;
                st[hi].erase(next);
            }
            else
                st[hi].insert(next);
        }
        merge(lo, hi);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", res[i]);
    return 0;
}