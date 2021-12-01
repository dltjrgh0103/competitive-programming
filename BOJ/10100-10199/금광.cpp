#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;

struct p {
	ll x, y, w;
	bool operator < (const p& t) const {
		if (x != t.x) return x < t.x;
		return y < t.y;
	}
};

struct Node {
	ll sum, l, r, lr;
};

int bias = 4096;
Node tree[8282];

void init() {
	for (int i = 0; i < 8282; i++) {
		tree[i].sum = tree[i].l = tree[i].r = tree[i].lr = 0;
	}
}

Node f(Node& a, Node& b) {
	Node ret;
	ret.sum = a.sum + b.sum;
	ret.l = max(a.l, a.sum + b.l);
	ret.r = max(b.r, a.r + b.sum);
	ret.lr = max({ a.r + b.l, a.lr, b.lr, ret.sum });
	return ret;
}

void update(int x, int v) {
	x |= bias; tree[x].sum = tree[x].l = tree[x].r = tree[x].lr += v;
	while (x >>= 1) {
		tree[x] = f(tree[x << 1], tree[x << 1 | 1]);
	}
}

Node query(int l, int r) {
	l |= bias, r |= bias;
	Node ret = { 0, 0, 0 };
	while (l <= r) {
		if (l & 1) ret = f(tree[l++], ret);
		if (~r & 1) ret = f(ret, tree[r--]);
		l >>= 1, r >>= 1;
	}
	return ret;
}

vector<p> v;
vector<ll> xx, yy;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n; v.resize(n);
	for (auto& i : v) {
		cin >> i.x >> i.y >> i.w;
		xx.push_back(i.x);
		yy.push_back(i.y);
	}
	sort(all(xx)); sort(all(yy));
	xx.erase(unique(all(xx)), xx.end());
	yy.erase(unique(all(yy)), yy.end());
	for (auto& i : v) {
		i.x = lower_bound(all(xx), i.x) - xx.begin();
		i.y = lower_bound(all(yy), i.y) - yy.begin();
		swap(i.x, i.y);
	}
	sort(all(v));

	ll ret = 0;

	for (int i = 0; i < n; i++) {
		if (i && v[i - 1].x == v[i].x) continue;
		init();
		for (int j = i; j < n; j++) {
			update(v[j].y, v[j].w);
			if (j == n - 1 || v[j].x != v[j + 1].x) ret = max(ret, tree[1].lr);
		}
	}
	cout << ret;
}