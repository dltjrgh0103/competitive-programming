#include <bits/stdc++.h>
using namespace std;

int c[444][444];
int f[444][444];
vector<int> g[444];
int s, t;
int lv[444];
int work[444];
int chk[444];

const int inf = 1e9;

int n, m;

void addEdge(int s, int e, int x = inf) {
	g[s].push_back(e); c[s][e] = x;
	g[e].push_back(s);
}

bool bfs() {
	memset(lv, -1, sizeof lv);
	queue<int> q; q.push(s); lv[s] = 0;
	while (q.size()) {
		int now = q.front(); q.pop();
		for (auto nxt : g[now]) {
			if (lv[nxt] == -1 && c[now][nxt] - f[now][nxt] > 0) {
				lv[nxt] = lv[now] + 1; q.push(nxt);
			}
		}
	}
	return lv[t] != -1;
}

int dfs(int now, int tot) {
	if (now == t) return tot;
	for (int& i = work[now]; i < g[now].size(); i++) {
		int nxt = g[now][i];
		if (lv[nxt] == lv[now] + 1 && c[now][nxt] - f[now][nxt] > 0) {
			int fl = dfs(nxt, min(tot, c[now][nxt] - f[now][nxt]));
			if (fl > 0) {
				f[now][nxt] += fl;
				f[nxt][now] -= fl;
				return fl;
			}
		}
	}
	return 0;
}

int dinic() {
	int ret = 0;
	while (bfs()) {
		memset(work, 0, sizeof work);
		while (1) {
			int fl = dfs(s, inf + 10);
			if (fl <= 0) break;
			ret += fl;
		}
	}
	return ret;
}

void solve() {
	dinic();
	queue<int> q; q.push(s); chk[s] = 1;
	while (q.size()) {
		int now = q.front(); q.pop();
		for (auto nxt : g[now]) {
			if (chk[nxt]) continue;
			if (c[now][nxt] - f[now][nxt] > 0) {
				q.push(nxt); chk[nxt] = 1;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (chk[i] && !chk[i + n]) cout << i << " ";
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	cin >> s >> t; t += n;
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		addEdge(i, i + n, x);
	}
	for (int i = 1; i <= m; i++) {
		int a, b; cin >> a >> b;
		addEdge(a + n, b);
		addEdge(b + n, a);
	}
	solve();
}