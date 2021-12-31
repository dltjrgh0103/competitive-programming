#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e18;
vector<vector<pair<int, ll>>> G(5005), rev_G(5005);
vector<ll> D;
ll dp[5005][5005];
ll pre[5005];
int N, B, S, M;

void dijkstra(int src, vector<vector<pair<int, ll>>>& G, vector<ll>& dist) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[src] = 0;
    pq.push(make_pair(dist[src], src));
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll d = pq.top().first;
        pq.pop();
        if (d > dist[cur]) continue;
        for (auto nxt : G[cur]) {
            int v = nxt.first;
            ll w = nxt.second;
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

void solve(int lev, int s, int e, int optl, int optr) {
    if (s > e) return;
    int mid = (s + e) >> 1;
    ll& ans = dp[lev][mid];
    ans = dp[lev - 1][optl] + (mid - optl - 1) * (pre[mid] - pre[optl]);
    int opt = optl;
    for (int i = optl; i < min(mid, optr); ++i) {
        ll val = dp[lev - 1][i] + (mid - i - 1) * (pre[mid] - pre[i]);
        if (ans > val) {
            ans = val; opt = i;
        }
    }
    solve(lev, s, mid - 1, optl, opt + 1);
    solve(lev, mid + 1, e, opt, optr);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N >> B >> S >> M;
    for (int i = 0; i < M; ++i) {
        int u, v; ll w;
        cin >> u >> v >> w;
        G[u].push_back({ v,w });
        rev_G[v].push_back({ u,w });
    }
    vector<ll> dist(N + 1), rev_dist(N + 1);
    fill(dist.begin(), dist.end(), INF);
    fill(rev_dist.begin(), rev_dist.end(), INF);
    dijkstra(B + 1, G, dist);
    dijkstra(B + 1, rev_G, rev_dist);
    D.resize(B + 1, 0);
    for (int i = 1; i <= B; ++i) D[i] = dist[i] + rev_dist[i];
    sort(D.begin(), D.end());
    for (int i = 1; i <= B; ++i) pre[i] = pre[i - 1] + D[i];
    for (int i = 1; i <= B; ++i) dp[1][i] = (i - 1) * pre[i];
    for (int i = 2; i <= S; ++i) solve(i, i, B, i - 1, B);
    cout << dp[S][B] << '\n';
    return 0;
}