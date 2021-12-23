#include<bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> T, V, dp;
int D, N;
ll ans;
ll cnt;
ll C(ll i, ll j) {
    return V[i] + (j - i) * T[j];
}

void solve(int s, int e, int optl, int optr) {
    if (s > e) return;
    int mid = (s + e) >> 1;
    int opt = mid;
    dp[mid] = V[mid];
    pair<ll, int> ret = { V[mid],mid };
    for (int i = optl; i <= min(optr, mid + D); ++i) {
        ll val = V[mid] + (i - mid) * T[i];
        if (dp[mid] < val) {
            dp[mid] = val; opt = i;
        }
    }
    solve(s, mid - 1, optl, opt);
    solve(mid + 1, e, opt, optr);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N >> D;
    T.resize(N + 1); V.resize(N + 1); dp.resize(N + 1);
    for (int i = 1; i <= N; ++i) cin >> T[i];
    for (int i = 1; i <= N; ++i) cin >> V[i];
    solve(1, N, 1, N);
    for (int i = 1; i <= N; ++i) ans = max(ans, dp[i]);
    cout << ans << '\n';
    return 0;
}