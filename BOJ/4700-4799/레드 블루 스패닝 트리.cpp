#include <bits/stdc++.h>
using namespace std;

int par[1010];
int find(int v) {
	if (v == par[v]) return v;
	return par[v] = find(par[v]);
}
int merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return 0;
	par[u] = v;
	return 1;
}

struct edge {
	char color;
	int s, e;
	edge() {}
	edge(char x, int y, int z) : color(x), s(y), e(z) {}
};

vector<edge> v;

bool redFirstSort(edge& a, edge& b) {
	return a.color > b.color;
}

bool blueFirstSort(edge& a, edge& b) {
	return a.color < b.color;
}

int mst(int n) {
	int cnt = 0, ret = 0;
	for (int i = 0; i <= n; i++) par[i] = i;
	for (int i = 0; i < v.size(); i++) {
		if (merge(v[i].s, v[i].e)) {
			if (v[i].color == 'B') ret++;
			cnt++;
		}
		if (cnt == n - 1) break;
	}
	return ret;
}

void f(int n, int m, int k) {
	v.clear();
	for (int i = 0; i < m; i++) {
		char c; int s, e;
		cin >> c >> s >> e;
		v.push_back({ c, s, e });
	}
	int a, b;
	sort(v.begin(), v.end(), redFirstSort);
	a = mst(n);
	sort(v.begin(), v.end(), blueFirstSort);
	b = mst(n);
	if (a <= k && k <= b) cout << "1\n";
	else cout << "0\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	while (1) {
		int n, m, k; cin >> n >> m >> k;
		if (!n && !m && !k) break;
		f(n, m, k);
	}
}