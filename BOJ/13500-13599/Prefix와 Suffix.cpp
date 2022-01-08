#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

vector<int> pi;
string a;
int t, g[100001], tg[100001], SA[100001], r[100001], LCP[100001];
vector<pair<int, int>> res;

bool cmp(int x, int y) {
    if (g[x] == g[y])return g[x + t] < g[y + t];
    return g[x] < g[y];
}
void getpi() {
    pi.resize(a.length());
    int j = 0;

    for (int i = 1; i < a.length(); i++) {
        while (j && a[i] != a[j])
            j = pi[j - 1];
        if (a[i] == a[j])
            pi[i] = ++j;
    }
}

int dp[100005];
int func(int x) {
    int& ret = dp[x];
    if (ret != -1)return ret;
    ret = 1;

    for (int i = x + 1; i < a.length(); i++) {
        if (LCP[i] >= a.length() - SA[x]) {
            ret += func(i);
            i += func(i) - 1;
        }
        else break;
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    cin >> a;
    getpi();
    t = 1;

    for (int i = 0; i < a.length(); i++) {
        SA[i] = i;
        g[i] = a[i] - 'A';
    }

    while (t <= a.length()) {
        g[a.length()] = -1;
        sort(SA, SA + a.length(), cmp);
        tg[SA[0]] = 0;

        for (int i = 1; i < a.length(); i++) {
            if (cmp(SA[i - 1], SA[i]))
                tg[SA[i]] = tg[SA[i - 1]] + 1;
            else
                tg[SA[i]] = tg[SA[i - 1]];
        }

        for (int i = 0; i < a.length(); i++)
            g[i] = tg[i];
        t <<= 1;
    }

    for (int i = 0; i < a.length(); i++)
        r[SA[i]] = i;

    int len = 0;
    for (int i = 0; i < a.length(); i++) {
        int k = r[i];
        if (k) {
            int j = SA[k - 1];
            while (a[j + len] == a[i + len])
                len++;
            LCP[k] = len;
            if (len)len--;
        }
    }

    for (int i = 0; i < a.length(); i++)
        func(i);
    res.push_back({ a.length(),1 });

    int x = pi[a.length() - 1];
    while (x) {
        int idx = r[a.length() - x];
        res.push_back({ x,dp[idx] });
        x = pi[x - 1];
    }
    printf("%d\n", res.size());

    for (int i = res.size() - 1; i >= 0; i--)
        printf("%d %d\n", res[i].first, res[i].second);

    return 0;
}