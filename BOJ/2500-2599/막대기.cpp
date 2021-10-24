#include <bits/stdc++.h>
using namespace std;

int n;
int X1[3030], Y1[3030], X2[3030], Y2[3030];
vector<int> gph[6060], rev[6060], dfn;
int chk[6060], scc[6060];

inline int inv(int x) {
	if (x >= 3 * n) return x - 3 * n;
	else return x + 3 * n;
}

int ccw(int a, int b, int c, int d, int e, int f) {
	int res = (c - a) * (f - b) - (d - b) * (e - a);
	return res > 0 ? 1 : -1;
}

bool cross(int i, int j) {
	int t1 = ccw(X1[i], Y1[i], X2[i], Y2[i], X1[j], Y1[j]) * ccw(X1[i], Y1[i], X2[i], Y2[i], X2[j], Y2[j]);
	int t2 = ccw(X1[j], Y1[j], X2[j], Y2[j], X1[i], Y1[i]) * ccw(X1[j], Y1[j], X2[j], Y2[j], X2[i], Y2[i]);
	return t1 < 0 && t2 < 0;
}

void dfs1(int v) {
	chk[v] = 1;
	for (auto i : gph[v]) if (!chk[i]) dfs1(i);
	dfn.push_back(v);
}

void dfs2(int v, int color) {
	scc[v] = color;
	for (auto i : rev[v]) if (!scc[i]) dfs2(i, color);
}

void getSCC() {
	for (int i = 0; i < 6 * n; i++) if (!chk[i]) dfs1(i);
	reverse(dfn.begin(), dfn.end());
	int cnt = 1;
	for (auto i : dfn) {
		if (!scc[i]) dfs2(i, cnt++);
	}
}

void addEdge(int a, int b) {
	gph[a].push_back(b);
	rev[b].push_back(a);
	gph[inv(b)].push_back(inv(a));
	rev[inv(a)].push_back(inv(b));
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < 3 * n; i++) {
		cin >> X1[i] >> Y1[i] >> X2[i] >> Y2[i];
	}
	for (int i = 0; i < n; i++) {
		addEdge(3 * i, inv(3 * i + 1));
		addEdge(3 * i, inv(3 * i + 2));
		addEdge(3 * i + 1, inv(3 * i));
		addEdge(3 * i + 1, inv(3 * i + 2));
		addEdge(3 * i + 2, inv(3 * i));
		addEdge(3 * i + 2, inv(3 * i + 1));
	}
	for (int i = 0; i < 3 * n; i++) {
		for (int j = i + 1; j < 3 * n; j++) {
			if (cross(i, j)) addEdge(inv(i), j);
		}
	}
	getSCC();
	vector<int> ans;
	for (int i = 0; i < 3 * n; i++) {
		if (scc[i] == scc[inv(i)]) {
			cout << -1; return 0;
		}
		if (scc[i] > scc[inv(i)]) ans.push_back(i + 1);
	}
	cout << ans.size() << "\n";
	for (auto i : ans) cout << i << " ";
}