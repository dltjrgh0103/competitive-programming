#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
#define MAXN 100001
int N, M, tsz;

struct Node {
    int l, r, val;
    Node() : l(0), r(0), val(0) {};
    Node(int _l, int _r, int _val) : l(_l), r(_r), val(_val) {};
};

void init(vector<Node>& tree) {
    int sz = tsz >> 1;
    for (int i = 1; i <= sz; ++i) {
        tree[i].l = i << 1; tree[i].r = i << 1 | 1;
    }
}

void update(vector<Node>& tree, int node, int s, int e, int val, int idx) {
    if (s != e) {
        int mid = (s + e) >> 1;
        int n1 = tree[node].l, n2 = tree[node].r;
        if (idx <= mid) {
            tree[node].l = tree.size();
            tree.push_back(Node(tree[n1].l, tree[n1].r, tree[n1].val + val));
            update(tree, tree[node].l, s, mid, val, idx);
        }
        else {
            tree[node].r = tree.size();
            tree.push_back(Node(tree[n2].l, tree[n2].r, tree[n2].val + val));
            update(tree, tree[node].r, mid + 1, e, val, idx);
        }
    }
}

int query(vector<Node>& tree, int node, int s, int e, int l, int r) {
    if (r < s || l > e) return 0;
    if (l <= s && e <= r) return tree[node].val;
    int mid = (s + e) >> 1;
    int n1 = tree[node].l, n2 = tree[node].r;
    return query(tree, n1, s, mid, l, r) + query(tree, n2, mid + 1, e, l, r);
}

int roots[100005];
vector<Node> tree;
int main() {
    tsz = 1;
    while (tsz < MAXN) tsz <<= 1;
    tsz <<= 1;
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int tc; cin >> tc;
    while (tc--) {
        cin >> N >> M;
        vector<vector<int>> yval(MAXN + 1);
        tree = vector<Node>(tsz);
        for (int i = 0; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            ++x; ++y;
            yval[x].push_back(y);
        }
        init(tree);
        roots[0] = 1;
        for (int i = 1; i <= MAXN; ++i) {
            roots[i] = tree.size();
            int pi = roots[i - 1];
            tree.push_back(Node(tree[pi].l, tree[pi].r, tree[pi].val));
            for (auto y : yval[i]) {
                tree[roots[i]].val += 1;
                update(tree, roots[i], 1, MAXN, 1, y);
            }
        }
        long long ans = 0;
        for (int i = 0; i < M; ++i) {
            int l, r, b, t;
            cin >> l >> r >> b >> t;
            ++r; ++b; ++t;
            ans += query(tree, roots[r], 1, MAXN, b, t) - query(tree, roots[l], 1, MAXN, b, t);
        }
        cout << ans << '\n';
    }
    return 0;
}