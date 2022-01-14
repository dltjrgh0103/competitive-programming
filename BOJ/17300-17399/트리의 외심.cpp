#include<bits/stdc++.h>

using namespace std;
const int SZ = 100005;
const int MXH = 18;
vector<int> graph[SZ];

int par[MXH][SZ];
int lv[SZ];
int vst[SZ];
int n;

void dfs(int x, int parent, int level) {
	vst[x] = 1;
	par[0][x] = parent;
	lv[x] = level;

	for (int nxt : graph[x]) {
		if (vst[nxt] == 1) continue;
		dfs(nxt, x, level + 1);
	}
}

void memo() {
	for (int i = 1; i < MXH; i++) {
		for (int j = 1; j <= n; j++) {
			par[i][j] = par[i - 1][par[i - 1][j]];
		}
	}
}

int level_up(int x, int diff) {
	for (int i = MXH - 1; i >= 0; i--) {
		if ((1 << i) & diff) x = par[i][x];
	}

	return x;
}

int lca(int x, int y) {
	x = level_up(x, max(0, lv[x] - lv[y]));
	y = level_up(y, max(0, lv[y] - lv[x]));
	if (x == y) return x;
	for (int i = MXH - 1; i >= 0; i--) {
		if (par[i][x] != par[i][y]) {
			x = par[i][x];
			y = par[i][y];
		}
	}

	return par[0][x];
}

int tree_dist(int a, int b) {
	int l = lca(a, b);
	return lv[a] + lv[b] - 2 * lv[l];
}

int iso(int a, int b) {
	int up = tree_dist(a, b);
	if (up % 2 == 1) return -1;

	if (lv[a] > lv[b]) return level_up(a, up / 2);
	else return level_up(b, up / 2);
}

int query(int a, int b, int c) {
	int m1 = iso(a, b);
	int m2 = iso(a, c);
	int m3 = iso(b, c);

	if (m1 != -1) {
		if (tree_dist(a, m1) == tree_dist(b, m1) && tree_dist(b, m1) == tree_dist(c, m1)) return m1;
	}
	if (m2 != -1) {
		if (tree_dist(a, m2) == tree_dist(b, m2) && tree_dist(b, m2) == tree_dist(c, m2)) return m2;
	}
	if (m3 != -1) {
		if (tree_dist(a, m3) == tree_dist(b, m3) && tree_dist(b, m3) == tree_dist(c, m3)) return m3;
	}

	return -1;
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;

	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	dfs(1, 0, 0);
	memo();

	int q; cin >> q;
	while (q--) {
		int x, y, z; cin >> x >> y >> z;
		cout << query(x, y, z) << '\n';
	}

	return 0;
}