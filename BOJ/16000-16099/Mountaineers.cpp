#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;
typedef pair<int, int> p;

struct Edge {
    int s, e, x;
    Edge(int s, int e, int x) : s(s), e(e), x(x) {}
    
    bool operator < (const Edge& t) const {
        return tie(x, s, e) < tie(t.x, t.s, t.e);
    }
};

int par[252525];
void init() { iota(par, par + 252525, 0); }

int find(int v) { return v == par[v] ? v : par[v] = find(par[v]); }
void merge(int u, int v) { u = find(u); v = find(v); if (u != v) par[u] = v; }
bool is_con(int u, int v) { return find(u) == find(v); }
inline int id(int u, int v) { return u * 500 + v; }

int n, m, q, c[555][555];
vector<int> inp[555];
vector<Edge> edge;
p qry[505050];

ll l[505050], r[505050];
vector<vector<int>> batch;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) cin >> c[i][j];

    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        if (i + 1 <= n) edge.emplace_back(id(i, j), id(i + 1, j), max(c[i][j], c[i + 1][j]));
        if (j + 1 <= m) edge.emplace_back(id(i, j), id(i, j + 1), max(c[i][j], c[i][j + 1]));
    }
    sort(all(edge));

    for (int i = 1; i <= q; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        qry[i].x = id(a, b); qry[i].y = id(c, d);
    }

    for (int i = 1; i <= q; i++) l[i] = 0, r[i] = edge.size() - 1;
    batch.resize(edge.size());

    while (1) {
        int flag = 0;
        for (auto& i : batch) i.clear();

        for (int i = 1; i <= q; i++) if (l[i] < r[i]) {
            batch[l[i] + r[i] >> 1].push_back(i); flag = 1;
        }

        if (!flag) break;
        init();

        for (int i = 0; i < edge.size(); i++) {
            merge(edge[i].s, edge[i].e);
            for (auto j : batch[i]) {
                if (is_con(qry[j].x, qry[j].y)) r[j] = i;
                else l[j] = i + 1;
            }
        }
    }

    for (int i = 1; i <= q; i++) {
        if (qry[i].x == qry[i].y) cout << c[qry[i].x / 500][qry[i].x % 500] << "\n";
        else cout << edge[r[i]].x << "\n";
    }
}