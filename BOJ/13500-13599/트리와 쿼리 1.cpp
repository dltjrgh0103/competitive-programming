#include<bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ppi = pair<int, pii>;

const int nmax = 100010;

#define fi first
#define se second

#define fastio do{ios::sync_with_stdio(0);cin.tie(0);}while(0)

#define radj(x) for(auto [nxt,wei]:adj[x])

int n, m;
vector<pii> adj[nmax];
vector<ppi> edge;
int seg[nmax << 2];
int w[nmax];
int d[nmax];
int v[nmax];
int sps[20][nmax];
int idx[nmax];
int rev[nmax];
int hld[nmax];

void su(int idx, int l, int r, int p, int x) {
    if (l > p || r < p)return;
    if (l != r) {
        int mid = l + r >> 1;
        su(idx << 1, l, mid, p, x); su((idx << 1) + 1, mid + 1, r, p, x);
        seg[idx] = max(seg[idx << 1], seg[(idx << 1) + 1]);
        return;
    }
    seg[idx] = v[l] = x;
}

int sq(int idx, int l, int r, int s, int e) {
    if (l > e || r < s)return 0;
    if (s <= l && r <= e)return seg[idx];
    int mid = l + r >> 1;
    return max(sq(idx << 1, l, mid, s, e), sq((idx << 1) + 1, mid + 1, r, s, e));
}

int lca(int u, int v) {
    if (d[u] > d[v])swap(u, v);
    for (int i = 19; i >= 0; i--)if (d[v] - d[u] >= (1 << i))v = sps[i][v];
    if (u == v)return u;
    for (int i = 19; i >= 0; i--)if (sps[i][u] != sps[i][v]) {
        u = sps[i][u]; v = sps[i][v];
    }
    return sps[0][u];
}

void dfs(int now) {
    w[now] = 1;
    radj(now)if (!w[nxt]) {
        v[nxt] = wei;
        sps[0][nxt] = now;
        d[nxt] = d[now] + 1;
        dfs(nxt);
        w[now] += w[nxt];
    }
}

int dn;
void dfs2(int now) {
    int cc = -1;
    idx[now] = ++dn;
    rev[idx[now]] = now;
    radj(now)
        if (sps[0][nxt] == now && (cc == -1 || w[nxt] > w[cc]))
            cc = nxt;
    if (cc != -1) {
        hld[cc] = hld[now];
        dfs2(cc);
    }
    radj(now)if (sps[0][nxt] == now && nxt != cc) {
        hld[nxt] = nxt;
        dfs2(nxt);
    }
}

void hld_upd(int eidx, int x) {
    if (d[edge[eidx].se.fi] > d[edge[eidx].se.se]) {
        su(1, 1, n, idx[edge[eidx].se.fi], x);
    }
    else {
        su(1, 1, n, idx[edge[eidx].se.se], x);
    }
}

int hld_hq(int u, int v) {
    int r = 0;
    while (hld[u] != hld[v]) {
        r = max(r, sq(1, 1, n, idx[hld[u]], idx[u]));
        u = sps[0][hld[u]];
    }
    if (u != v) {
        r = max(r, sq(1, 1, n, idx[v] + 1, idx[u]));
    }
    return r;
}

int hld_query(int u, int v) {
    int l = lca(u, v);
    return max(hld_hq(u, l), hld_hq(v, l));
}

int main(void) {
    fastio;

    cin >> n;
    edge.resize(n - 1);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edge[i - 1] = ppi(c, pii(a, b));
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }

    dfs(1); dfs2(1);
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            sps[i][j] = sps[i - 1][sps[i - 1][j]];
        }
    }
    for (int i = 0; i < n - 1; i++) {
        hld_upd(i, edge[i].fi);
    }

    cin >> m;
    while (m--) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) {
            edge[a - 1].fi = b;
            hld_upd(a - 1, b);
        }
        else {
            cout << hld_query(a, b) << "\n";
        }
    }
}