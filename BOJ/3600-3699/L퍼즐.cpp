#include <bits/stdc++.h>
using namespace std;

// Left, Up, Right, Down
const int di[] = { 0, -1, 0, 1 };
const int dj[] = { -1, 0, 1, 0 };

vector<int> G[1010101], R[1010101], dfn;
int C[1010101];

void DFS(int v) {
    C[v] = 1;
    for (const auto& i : G[v]) if (!C[i]) DFS(i);
    dfn.push_back(v);
}
void DFS2(int v, int color) {
    C[v] = color;
    for (const auto& i : R[v]) if (!C[i]) DFS2(i, color);
}

void SCC(int N) {
    for (int i = 0; i < N; i++) if (!C[i]) DFS(i);
    reverse(dfn.begin(), dfn.end());
    memset(C, 0, sizeof C);
    int pv = 0;
    for (const auto& i : dfn) if (!C[i]) DFS2(i, ++pv);
}

bool TwoSat(int N) {
    SCC(N << 1 | 1);
    for (int i = 1; i <= N; i++) if (C[i] == C[i + N]) return false;
    return true;
}

int N, M; char A[555][555];
inline int Inv(int x) { return x <= 2 * N * M ? x + 2 * N * M : x - 2 * N * M; }

void Edge(int s, int e) {
    G[s].push_back(e);
    R[e].push_back(s);
}

void CNF(int a, int b) { /// a or b
    if (a < 0) a = Inv(-a);
    if (b < 0) b = Inv(-b);
    Edge(Inv(a), b);
    Edge(Inv(b), a);
}

void Init() {
    memset(A, '.', sizeof A);
    memset(C, 0, sizeof C);
    for (int i = 0; i < 1010101; i++) G[i].clear(), R[i].clear();
    dfn.clear();
}

void Solve() {
    Init();
    cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];

    int black = 0, white = 0; // black * 2 == white
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            array<int, 4> id = {
                (i - 1) * M + j - 1,     // L
                (i - 2) * M + j + N * M, // U
                (i - 1) * M + j,       // R
                (i - 1) * M + j + N * M  // D
            };
            array<bool, 4> flags;
            for (int k = 0; k < 4; k++) flags[k] = A[i + di[k]][j + dj[k]] == 'B';
            if (A[i][j] == 'B') {
                black++;
                for (int k = 0; k < 2; k++) {
                    int t0 = A[i + di[k]][j + dj[k]] == 'W';
                    int t1 = A[i + di[k + 2]][j + dj[k + 2]] == 'W';
                    int a = id[k], b = id[k + 2];
                    if (t0 && t1) CNF(a, b), CNF(-a, -b);
                    else if (t0) CNF(a, a);
                    else if (t1) CNF(b, b);
                    else { cout << "NO\n"; return; }
                }
                for (int ii = 0; ii < 4; ii++) for (int jj = 0; jj < ii; jj++) if (flags[ii] && flags[jj]) CNF(id[ii], -id[ii]), CNF(id[jj], -id[jj]);
            }
            if (A[i][j] == 'W') {
                white++;
                for (int ii = 0; ii < 4; ii++) for (int jj = 0; jj < ii; jj++) if (flags[ii] && flags[jj]) CNF(-id[ii], -id[jj]);
            }
        }
    }
    if (black * 2 == white && TwoSat(2 * N * M)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T; while (T--) Solve();
}