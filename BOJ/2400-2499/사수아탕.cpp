#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int n, dp[333][333][2], x, m, res;
vector<int> v;
int func(int l, int r, int state, int rem) {
    if (!rem)return 0;
    if (l > r)return 1e9;
    int& ret = dp[l][r][state];
    if (ret != -1)return ret;
    ret = 1e9;
    if (state) {//¿Þ
        if (r != n)
            ret = min(ret, func(l, r + 1, 0, rem - 1) + rem * (v[r + 1] - v[l]));
        if (l)
            ret = min(ret, func(l - 1, r, 1, rem - 1) + rem * (v[l] - v[l - 1]));
    }
    else {//¿À
        if (r != n)
            ret = min(ret, func(l, r + 1, 0, rem - 1) + rem * (v[r + 1] - v[r]));
        if (l)
            ret = min(ret, func(l - 1, r, 1, rem - 1) + rem * (v[r] - v[l - 1]));
    }
    return ret;
}
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        v.push_back(x);
    }
    v.push_back(0);
    sort(v.begin(), v.end());
    memset(dp, -1, sizeof(dp));
    int idx = lower_bound(v.begin(), v.end(), 0) - v.begin();
    for (int i = 0; i <= n; i++) {
        memset(dp, -1, sizeof(dp));
        res = max(res, i * m - func(idx, idx, 0, i));
    }
    printf("%d\n", res);
    return 0;
}