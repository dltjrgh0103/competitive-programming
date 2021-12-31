#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cstring>
typedef long long ll;
using namespace std;
struct _ {
    ll x, y, i, d;
};

vector<_> vt;
int vst[2500];
int i;
_ base;
ll M;

int ccw(_ a, _ b, _ c) {
    ll res = a.x * b.y + b.x * c.y + c.x * a.y;
    res -= b.x * a.y + c.x * b.y + a.x * c.y;
    if (res > 0) return 1;
    if (res) return -1;
    return 0;
}

bool cmp(_ a, _ b) {
    int cw = ccw(base, a, b);
    if (cw)return cw > 0;
    return a.d > b.d;
}

void f(int now) {
    vector<_> v; base = vt[now];
    for (auto now : vt) {
        if (now.y == vt[i].y) continue;
        if (now.y < vt[i].y) {
            ll xx = vt[i].x + vt[i].x - now.x;
            ll yy = vt[i].y + vt[i].y - now.y;
            v.push_back({ xx, yy, now.i, now.d });
        }
        else v.push_back(now);
    }

    sort(v.begin(), v.end(), cmp);
    for (auto& now : v) {
        if (vst[now.i]) {
            now.d *= -1;
        }
        else vst[now.i] = 1;
    }
    sort(v.begin(), v.end(), cmp);
    ll res = 0;
    M = max(M, vt[i].d);
    for (auto now : v) {
        res += now.d;
        M = max(res + vt[i].d, M);
    }
}
int main() {
    cin.tie(0), ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for (i = 1; i <= n; i++) {
        int x0, x1, y;
        cin >> x0 >> x1 >> y;
        if (x0 > x1)swap(x0, x1);
        vt.push_back({ x0,y,i,x1 - x0 });
        vt.push_back({ x1,y,i,x1 - x0 });
    }

    for (i = 0; i < 2 * n; i++) {
        f(i);
        memset(vst, 0, sizeof(vst));
    }
    cout << M;
}