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
vector<ll> v;
bool ans = 0;
ll cnt[202020];
ll l[1010101];
ll r[1010101];

void sol(ll s, ll e) {
    //printf("%lld %lld\n",s,e);
    if (s >= e) return;
    if (ans) return;
    ll mid = (s + e) / 2;
    ll x = 0;
    ll i;
    for (x = 0; x <= (e - s) / 2; x++) {
        i = s + x;
        if (l[i]<s && r[i]>e) {
            sol(s, i - 1);
            sol(i + 1, e);
            return;
        }
        i = e - x;
        if (l[i]<s && r[i]>e) {
            sol(s, i - 1);
            sol(i + 1, e);
            return;
        }
    }
    ans = 1;
    return;
}

vector<ll> v2[1010101];

int main() {
    ll t;
    scanf("%lld", &t);
    while (t--) {
        ans = 0;
        v.clear();
        ll i, j, k, m, n;
        scanf("%lld", &n);
        for (i = 1; i <= n; i++) {
            scanf("%lld", &arr[i]);
            v.push_back(arr[i]);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (i = 1; i <= n; i++)
            arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin() + 1;

        for (i = 0; i <= n; i++) {
            l[i] = 0;
            r[i] = n + 1;
            v2[i].clear();
            v2[i].pb(0);
        }
        for (i = 1; i <= n; i++)
            v2[arr[i]].pb(i);
        for (i = 0; i <= n; i++)
            v2[i].pb(n + 1);

        for (i = 0; i <= n; i++)
            for (j = 1; j < v2[i].size(); j++) {
                l[v2[i][j]] = v2[i][j - 1];
                r[v2[i][j - 1]] = v2[i][j];
            }

        sol(1, n);
        if (ans) printf("boring\n");
        else printf("non-boring\n");
    }
}