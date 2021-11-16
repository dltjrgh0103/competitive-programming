#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 1e10;
int N;
ll a[1000005], pre[1000005], dp[1000005];
ll A, B, C;
int ptr;
struct Line {
    ll m, b;
    double x;
    Line(ll _m, ll _b, double _x) : m(_m), b(_b), x(_x) {};
    ll f(ll x) {
        return m * x + b;
    }
};
vector<Line> lines;

double intersect(Line& a, Line& b) {
    return (double)(b.b - a.b) / (a.m - b.m);
}

void addLine(ll m, ll b) {
    Line a(m, b, -INF);
    if (lines.empty()) {
        lines.push_back(a);
        return;
    }
    while (!lines.empty()) {
        Line top = lines.back();
        double x = intersect(top, a);
        if (x <= top.x) lines.pop_back();
        else break;
    }
    a.x = intersect(lines.back(), a);
    lines.push_back(a);
    if (ptr >= lines.size()) ptr = lines.size() - 1;
    return;
}

ll query(ll x) {
    while (ptr < lines.size() - 1 && lines[ptr + 1].x < x) ++ptr;
    return lines[ptr].f(x);
}

ll f(ll x) {
    return A * x * x + B * x + C;
}

ll slope(int i) {
    return -2 * A * pre[i];
}

ll inter(int i) {
    return A * pre[i] * pre[i] - B * pre[i] + dp[i];
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> N;
    cin >> A >> B >> C;
    for (int i = 1; i <= N; ++i) cin >> a[i];
    for (int i = 1; i <= N; ++i) pre[i] = pre[i - 1] + a[i];
    dp[1] = f(pre[1]);
    addLine(slope(1), inter(1));
    for (int i = 2; i <= N; ++i) {
        dp[i] = max(f(pre[i]), query(pre[i]) + f(pre[i]));
        addLine(slope(i), inter(i));
    }
    cout << dp[N] << '\n';
    return 0;
}
