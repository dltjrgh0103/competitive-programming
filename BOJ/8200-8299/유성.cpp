#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pii;

#define ff first
#define ss second
#define ep emplace_back
#define eb emplace
#define pb push_back

ll arr[1010101];
ll fin[1010101];
vector<ll> v[1010101];
ll ls[1010101];
ll le[1010101];
ll ans[1010101];
ll vis[1010101];

struct poi {
    ll lu, ru, au;
};

poi qwer[1010101];

void pre(ll s, ll e) {
    if (e <= s) return;
    ll mid = (s + e) / 2;
    ls[mid] = s;
    le[mid] = e;
    pre(mid + 1, e);
    pre(s, mid);
}

vector<ll> q1[1010101];
vector<ll> vn[101];
ll nn = 2222222;
ll tree[4040404];
void upt(ll idx, ll val) {
    while (idx <= nn) {
        tree[idx] += val;
        idx += idx & -idx;
    }
}

ll sum(ll x) {
    ll val = tree[x];
    while (x -= x & -x) val += tree[x];
    return val;
}

ll sol(ll l, ll r) {
    return sum(r) - sum(l - 1);
}

int main() {
    ll i, j, k, l, m, n;
    scanf("%lld %lld", &n, &m);
    for (i = 1; i <= m; i++) {
        scanf("%lld", &k);
        v[k].pb(i);
    }
    for (i = 1; i <= n; i++)
        scanf("%lld", &fin[i]);
    ll q;
    scanf("%lld", &q);
    for (i = 1; i <= q; i++)
        scanf("%lld %lld %lld", &qwer[i].lu, &qwer[i].ru, &qwer[i].au);

    pre(1, q + 1);
    for (i = 1; i <= n; i++)
        q1[q / 2 + 1].pb(i);

    ll t;
    vn[1].pb(q / 2 + 1);
    for (t = 1; t <= 22; t++) {
        sort(vn[t].begin(), vn[t].end());
        vn[t].erase(unique(vn[t].begin(), vn[t].end()), vn[t].end());
        ll fl = 1;
        for (auto k : vn[t]) {
            if (q1[k].size() == 0 || le[k] == 0 || vis[k]) continue;

            vis[k] = 1;
            while (fl <= k) {
                ll lu = qwer[fl].lu;
                ll ru = qwer[fl].ru;
                ll au = qwer[fl].au;
                if (qwer[fl].lu <= qwer[fl].ru) {
                    upt(lu, au);
                    upt(ru + 1, -au);
                }
                else {
                    upt(lu, au);
                    upt(ru + 1, -au);
                    upt(1, au);
                }
                fl++;
            }

            for (auto a : q1[k]) {
                ll val = 0;
                for (auto b : v[a]) {
                    val += sum(b);
                }
                if (val >= fin[a]) {
                    if (k <= ls[k]) ans[a] = k;
                    else q1[(ls[k] + k) / 2].pb(a);
                }
                else {
                    if (k + 1 >= le[k]) ans[a] = k + 1;
                    else q1[(le[k] + k + 1) / 2].pb(a);
                }
            }

            vn[t + 1].pb((ls[k] + k) / 2);
            vn[t + 1].pb((le[k] + k + 1) / 2);

        }
        for (ll p = 1; p <= 2323232; p++)
            tree[p] = 0;
    }

    for (i = 1; i <= n; i++) {
        if (ans[i] <= q) printf("%lld\n", ans[i]);
        else printf("NIE\n");
    }
}