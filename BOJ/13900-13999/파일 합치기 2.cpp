#include <bits/stdc++.h>
using namespace std;

int dp[510][510], K[510][510];

void solve(int n) {
	vector<int> v(n + 1), s(n + 1);

	for (int i = 1; i <= n; i++) cin >> v[i], s[i] = s[i - 1] + v[i];
	for (int i = 1; i <= n; i++) dp[i - 1][i] = 0, K[i - 1][i] = i;

	for (int m = 2; m <= n; m++) {
		for (int i = 0; m + i <= n; i++) {
			int j = i + m; dp[i][j] = 1e9 + 7;
			for (int k = K[i][j - 1]; k <= K[i + 1][j]; k++) {
				int now = dp[i][k] + dp[k][j] + s[j] - s[i];
				if (dp[i][j] > now) {
					dp[i][j] = now; K[i][j] = k;
				}
			}
		}
	}

	cout << dp[0][n] << "\n";
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		solve(n);
	}
}