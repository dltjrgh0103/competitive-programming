#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int MAXN = 500001;
const int INF = 1e9;

int n;
vector<vector<int>> score;
int tree[MAXN * 4];

int update(int index, int target, int value, int start, int end) {
	if (target < start || target > end)
		return tree[index];
	if (start == end)
		return tree[index] = value;
	else {
		int mid = (start + end) / 2;
		return tree[index] = min(update(index * 2, target, value, start, mid),
			update(index * 2 + 1, target, value, mid + 1, end));
	}
}

int query(int index, int left, int right, int start, int end) {
	if (left > end || right < start)
		return INF;
	if (left <= start && end <= right)
		return tree[index];
	int mid = (start + end) / 2;
	return min(query(index * 2, left, right, start, mid),
		query(index * 2 + 1, left, right, mid + 1, end));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	score.resize(n + 1);
	for (int i = 1; i <= n; ++i)
		score[i].resize(3);
	int t;
	for (int i = 0; i < 3; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> t;
			score[t][i] = j;
		}
	}
	sort(score.begin(), score.end());
	fill(&tree[0], &tree[n * 4], INF);

	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (query(1, 1, score[i][1], 1, n) > score[i][2])
			++res;
		update(1, score[i][1], score[i][2], 1, n);
	}
	cout << res << endl;
	return 0;
}