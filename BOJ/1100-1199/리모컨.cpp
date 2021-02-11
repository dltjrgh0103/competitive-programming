#include <iostream>
using namespace std;

int len = 0;
int result = 2147483647;
int N, M;
bool num[10] = { false, };

void ff(int idx, int val, int k) {
	if (len > 1 && idx == len - 1) {
		result = min(result, abs(N - val) + idx);
	}
	if (idx == len) {
		result = min(result, abs(N - val) + idx);
	}
	if (idx == len + 1) {
		result = min(result, abs(N - val) + idx);
		return;
	}

	for (int i = 0; i < 10; i++) {
		if (!num[i]) ff(idx + 1, val + i * k, k * 10);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int NN = N;
	while (1) {
		NN = NN / 10;
		len++;
		if (NN == 0) break;
	}

	for (int i = 0; i < M; i++) {
		int a;
		cin >> a;
		num[a] = true;
	}

	ff(0, 0, 1);
	if (result > abs(N - 100)) cout << abs(N - 100);
	else cout << result;
	return 0;
}