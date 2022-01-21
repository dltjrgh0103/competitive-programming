#include <bits/stdc++.h>
using namespace std;

const int sq = 400;
const int sz = 202020 / sq + 10;

struct Query {
	int s, e, x;
	Query() {}
	Query(int s, int e, int x) : s(s), e(e), x(x) {}
	bool operator < (const Query& t) const {
		if (s / sq != t.s / sq) return s < t.s;
		return e < t.e;
	}
};

int n, k, q;
int arr[202020];
vector<Query> qry;

list<int> pos[202020];
int cnt[202020], bucket[sz];
int ans[202020];

void Plus(int x, int dir) {
	int now = 0;
	auto& dq = pos[arr[x]];
	if (!dq.empty()) {
		now = dq.back() - dq.front();
		cnt[now]--;
		bucket[now / sq]--;
	}
	if (!dir) dq.push_front(x);
	else dq.push_back(x);
	now = dq.back() - dq.front();
	cnt[now]++; bucket[now / sq]++;
}

void Minus(int x, int dir) {
	auto& dq = pos[arr[x]];
	int now = dq.back() - dq.front();
	cnt[now]--; bucket[now / sq]--;
	if (!dir) dq.pop_front();
	else dq.pop_back();
	if (!dq.empty()) {
		now = dq.back() - dq.front();
		cnt[now]++; bucket[now / sq]++;
	}
}

int query() {
	for (int i = sz - 1; i >= 0; i--) {
		if (bucket[i] == 0) continue;
		for (int j = sq - 1; j >= 0; j--) {
			if (cnt[i * sq + j] > 0) {
				return i * sq + j;
			}
		}
	}
	return 0;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> arr[i];
	for (int i = 1; i <= n; i++) arr[i] += arr[i - 1];
	for (int i = 0; i <= n; i++) arr[i] += 100000;
	cin >> q;
	for (int i = 0; i < q; i++) {
		int s, e; cin >> s >> e;
		qry.push_back({ s - 1, e, i });
	}
	sort(qry.begin(), qry.end());

	int s = qry[0].s, e = qry[0].e, x = qry[0].x;
	for (int i = s; i <= e; i++) {
		Plus(i, 1);
	}
	ans[x] = query();

	for (int i = 1; i < q; i++) {
		x = qry[i].x;
		while (qry[i].s < s) Plus(--s, 0);
		while (e < qry[i].e) Plus(++e, 1);
		while (s < qry[i].s) Minus(s++, 0);
		while (qry[i].e < e) Minus(e--, 1);
		ans[x] = query();
	}

	for (int i = 0; i < q; i++) cout << ans[i] << "\n";
}