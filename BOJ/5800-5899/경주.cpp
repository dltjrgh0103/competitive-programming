#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 200000;
const int MXK = 1000000;
const int INF = 1e9;
int sub_sz[MXN + 5];
bool vis[MXN + 5];
int min_depth[MXK + 5];
vector<int> cur_tree;
vector<vector<pair<int, int>>> G(MXN + 5);
int N, K;

int get_size(int cur, int par) {
    sub_sz[cur] = 1;
    for (const auto& nxt : G[cur]) {
        int v = nxt.first;
        if (v == par || vis[v]) continue;
        sub_sz[cur] += get_size(v, cur);
    }
    return sub_sz[cur];
}

// return centroid of subtree which has cur as root
int get_cent(int cur, int par, int thr) {
    for (const auto& p : G[cur]) {
        int v = p.first;
        if (v == par || vis[v]) continue;
        if (sub_sz[v] > thr) return get_cent(v, cur, thr);
    }
    return cur;
}

int solve(int cur, int par, int dist, int depth) {
    int ret = INF;
    if (dist > K) return ret;
    ret = min(ret, min_depth[K - dist] + depth);
    for (const auto& p : G[cur]) {
        int v = p.first;
        int w = p.second;
        if (v == par || vis[v]) continue;
        ret = min(ret, solve(v, cur, dist + w, depth + 1));
    }
    return ret;
}

void update(int cur, int par, int dist, int depth) {
    if (dist > K) return;
    min_depth[dist] = min(min_depth[dist], depth);
    cur_tree.push_back(dist);
    for (const auto& p : G[cur]) {
        int v = p.first;
        int w = p.second;
        if (v == par || vis[v]) continue;
        update(v, cur, dist + w, depth + 1);
    }
}

int dnc(int cur) {
    int thr = get_size(cur, -1);
    int ct = get_cent(cur, -1, thr / 2); // Centroid Found
    vis[ct] = 1;                    // remove centroid from tree
    int ret = INF;
    for (const auto& a : cur_tree) min_depth[a] = INF;
    cur_tree.clear();
    min_depth[0] = 0;
    for (const auto& p : G[ct]) {      // now we can divide tree into subtrees <= thr
        int v = p.first;
        int w = p.second;
        if (!vis[v]) {
            ret = min(ret, solve(v, ct, w, 1));      // conquer subtrees
            update(v, ct, w, 1);
        }
    }
    for (const auto& p : G[ct]) {
        int v = p.first;
        if (vis[v]) continue;
        ret = min(ret, dnc(v));
    }
    return ret;
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N >> K;
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }
    for (int i = 0; i <= MXK; ++i) min_depth[i] = INF;
    int ans = dnc(0);
    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}
