#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> p;

template <typename T>
class SegTree {
private:
	T tree[808080];
	int lim;
	function<T(const T a, const T b)> f;
public:
	void init(int n, function<T(const T a, const T b)> func) {
		f = func;
		for (lim = 1; lim <= n; lim <<= 1);
	}
	void update(int x, T v) {
		x += lim;
		tree[x] = v;
		while (x > 1) {
			x >>= 1;
			tree[x] = f(tree[2 * x], tree[2 * x + 1]);
		}
	}
	T query(int s, int e) {
		s += lim;
		e += lim;
		T ret = 1;
		while (s < e) {
			if (s % 2 == 1) ret = f(ret, tree[s++]);
			if (e % 2 == 0) ret = f(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if (s == e) ret = f(ret, tree[s]);
		return ret;
	}
};

template <typename T>
class HLD {
private:
	int dn;
	int par[202020], size[202020], depth[202020], lab[202020];
	int id[202020], top[202020];
	SegTree<T> tree;
	function<T(const T a, const T b)> f;

	int dfs(int now, int prv) {
		par[now] = prv; size[now] = 1;
		for (auto& t : g[now]) {
			int nxt = t.first;
			if (nxt != prv) {
				depth[nxt] = depth[now] + 1;
				size[now] += dfs(nxt, now);
			}
		}
		return size[now];
	}
	void decom(int now, int prv, int chain) {
		lab[now] = dn;
		id[dn] = chain;
		top[chain] = dn++;
		int heavy = -1;
		for (auto& t : g[now]) {
			int nxt = t.first;
			if (nxt != prv && (heavy == -1 || size[nxt] > size[heavy])) heavy = nxt;
		}
		if (heavy != -1) decom(heavy, now, chain);
		for (auto& t : g[now]) {
			int nxt = t.first;
			if (nxt != prv && nxt != heavy) decom(nxt, now, nxt);
		}
	}

public:
	vector<p> g[202020];

	void init(int root, function<T(const T a, const T b)> func) {
		//init value
		f = func;
		dn = 0;
		memset(id, -1, sizeof(id));
		memset(top, -1, sizeof(top));

		//pre-processing
		dfs(root, -1);
		decom(root, -1, root);

		//set edge's weight
		vector<T> a(202020);
		for (int i = 0; i < 202020; i++) {
			for (auto& t : g[i]) {
				int next = t.first, w = t.second;
				int v = lab[next];
				if (depth[i] < depth[next]) a[v] = w;
			}
		}
		tree.init(a.size(), f);
		for (int i = 0; i < a.size(); i++) tree.update(i, a[i]);
	}

	void update(int u, int v, T k) {
		if (depth[u] < depth[v]) swap(u, v);
		tree.update(lab[u], k);
	}

	T query(int u, int v) {
		T ret = 1;
		u = lab[u], v = lab[v];
		while (id[u] != id[v]) {
			int uHead = id[u], vHead = id[v];
			if (depth[uHead] > depth[vHead]) {
				ret = f(ret, tree.query(lab[uHead], u));
				u = lab[par[uHead]];
			}
			else {
				ret = f(ret, tree.query(lab[vHead], v));
				v = lab[par[vHead]];
			}
		}
		ret = f(ret, tree.query(min(u, v) + 1, max(u, v)));
		return ret;
	}
};

HLD<int> hld;
vector<int> par(202020);

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q; cin >> n >> q;
	for (int i = 2; i <= n; i++) {
		int t; cin >> t;
		par[i] = t;
		hld.g[t].push_back({ i, 1 });
	}
	hld.init(1, [](int a, int b) {
		return a && b;
		});

	while (q--) {
		int a, b, op; cin >> a >> b >> op;
		int res = hld.query(a, b);
		if (res) cout << "YES\n";
		else cout << "NO\n";
		if (op == 1) {
			if (res) hld.update(a, par[a], 0);
			else hld.update(b, par[b], 0);
		}
	}
}