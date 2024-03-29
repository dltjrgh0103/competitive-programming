#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;
const ll mod = 1LL << 32;

struct Seg {
	ll tree[2020202];
	ll tmp[2020202][2];

	void push(int node, int s, int e) {
		if (tmp[node][0] == 1 && tmp[node][1] == 0) return;
		tree[node] *= tmp[node][0]; tree[node] %= mod;
		tree[node] += (e - s + 1) * tmp[node][1]; tree[node] %= mod;
		if (s ^ e) {
			tmp[node * 2][0] *= tmp[node][0]; tmp[node * 2][0] %= mod;
			tmp[node * 2][1] *= tmp[node][0]; tmp[node * 2][1] %= mod;
			tmp[node * 2][1] += tmp[node][1]; tmp[node * 2][1] %= mod;

			tmp[node * 2 + 1][0] *= tmp[node][0]; tmp[node * 2 + 1][0] %= mod;
			tmp[node * 2 + 1][1] *= tmp[node][0]; tmp[node * 2 + 1][1] %= mod;
			tmp[node * 2 + 1][1] += tmp[node][1]; tmp[node * 2 + 1][1] %= mod;
		}
		tmp[node][0] = 1, tmp[node][1] = 0;
	}

	void update(int node, int s, int e, int l, int r, ll mul, ll sum) {
		push(node, s, e);
		if (r < s || e < l) return;
		if (l <= s && e <= r) {
			tree[node] *= mul; tree[node] %= mod;
			tree[node] += (e - s + 1) * sum; tree[node] %= mod;
			if (s ^ e) {
				tmp[node * 2][0] *= mul; tmp[node * 2][0] %= mod;
				tmp[node * 2][1] *= mul; tmp[node * 2][1] %= mod;
				tmp[node * 2][1] += sum; tmp[node * 2][1] %= mod;

				tmp[node * 2 + 1][0] *= mul; tmp[node * 2 + 1][0] %= mod;
				tmp[node * 2 + 1][1] *= mul; tmp[node * 2 + 1][1] %= mod;
				tmp[node * 2 + 1][1] += sum; tmp[node * 2 + 1][1] %= mod;
			}
			return;
		}
		int m = s + e >> 1;
		update(node * 2, s, m, l, r, mul, sum);
		update(node * 2 + 1, m + 1, e, l, r, mul, sum);
		tree[node] = (tree[node * 2] + tree[node * 2 + 1]) % mod;
	}

	ll query(int node, int s, int e, int l, int r) {
		push(node, s, e);
		if (r < s || e < l) return 0;
		if (l <= s && e <= r) return tree[node];
		int m = s + e >> 1;
		ll t1 = query(node * 2, s, m, l, r);
		ll t2 = query(node * 2 + 1, m + 1, e, l, r);
		return (t1 + t2) % mod;
	}
} seg;

int in[505050], out[505050], top[505050], sz[505050], par[505050], dep[505050];
int chk[505050], pv;
int n, q;
vector<int> g[505050], inp[505050];

void dfs(int v = 1) {
	chk[v] = 1;
	for (auto i : inp[v]) {
		if (chk[i]) continue;
		chk[i] = 1;
		g[v].push_back(i);
		dfs(i);
	}
}

void dfs1(int v = 1) {
	sz[v] = 1;
	for (auto& i : g[v]) {
		dep[i] = dep[v] + 1; par[i] = v;
		dfs1(i); sz[v] += sz[i];
		if (sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
	}
}

void dfs2(int v = 1) {
	in[v] = ++pv;
	for (auto i : g[v]) {
		top[i] = i == g[v][0] ? top[v] : i;
		dfs2(i);
	}
	out[v] = pv;
}

void updateSub(int x, ll mul, ll sum) {
	seg.update(1, 1, n, in[x], out[x], mul, sum);
}

void updatePath(int a, int b, ll mul, ll sum) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		int st = top[a];
		seg.update(1, 1, n, in[st], in[a], mul, sum);
		a = par[st];
	}
	if (dep[a] > dep[b]) swap(a, b);
	seg.update(1, 1, n, in[a], in[b], mul, sum);
}

ll querySub(int x) {
	return seg.query(1, 1, n, in[x], out[x]);
}

ll queryPath(int a, int b) {
	ll ret = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		int st = top[a];
		ret += seg.query(1, 1, n, in[st], in[a]); ret %= mod;
		a = par[st];
	}
	if (dep[a] > dep[b]) swap(a, b);
	ret += seg.query(1, 1, n, in[a], in[b]); ret %= mod;
	return ret;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i < n; i++) {
		int s, e; cin >> s >> e;
		inp[s].push_back(e);
		inp[e].push_back(s);
	}
	dfs(); dfs1(); dfs2();

	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			ll a, b; cin >> a >> b;
			updateSub(a, 1, b);
		}
		else if (op == 2) {
			ll a, b, c; cin >> a >> b >> c;
			updatePath(a, b, 1, c);
		}
		else if (op == 3) {
			ll a, b; cin >> a >> b;
			updateSub(a, b, 0);
		}
		else if (op == 4) {
			ll a, b, c; cin >> a >> b >> c;
			updatePath(a, b, c, 0);
		}
		else if (op == 5) {
			ll a; cin >> a;
			cout << querySub(a) << "\n";
		}
		else if (op == 6) {
			ll a, b; cin >> a >> b;
			cout << queryPath(a, b) << "\n";
		}
	}
}