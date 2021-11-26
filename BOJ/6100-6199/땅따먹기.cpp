#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define xx first
#define yy second
const int MAX = 100000;

struct {
    int s = 0, e = 0, idx[MAX];
    pll deq[MAX];
    double cross(int a, int b) {
        return 1.0 * (deq[a].yy - deq[b].yy) / (deq[b].xx - deq[a].xx);
    }
    void insert(pll v, int line_idx) {
        deq[e] = v;
        idx[e] = line_idx;
        while (s + 1 < e && cross(e - 2, e - 1) > cross(e - 1, e)) {
            deq[e - 1] = deq[e];
            idx[e - 1] = idx[e];
            e--;
        }
        e++;
    }
    ll query(long long x) {
        while (s + 1 < e && deq[s + 1].yy - deq[s].yy <= x * (deq[s].xx - deq[s + 1].xx))
            s++;
        return deq[s].xx * x + deq[s].yy;
    }
} CHT;

int n;
vector<pll> input, V;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    sort(input.begin(), input.end());
    V.emplace_back(input[n - 1]);
    for (int i = n - 2; i >= 0; --i) {
        if (input[i].yy > V.back().yy)
            V.emplace_back(input[i]);
    }
    reverse(V.begin(), V.end());
    ll ret = 0;
    for (int i = 0; i < V.size(); ++i) {
        CHT.insert({ V[i].yy, ret }, i);
        ret = CHT.query(V[i].xx);
    }
    cout << ret;
}