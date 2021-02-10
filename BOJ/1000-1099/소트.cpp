#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<int> v;
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		v.push_back(t);
	}
	sort(v.begin(), v.end());

	int cnt = 0;
	for (int i = 0; i < v.size() - 1; i++) {
		if (v[i + 1] == v[i] + 1) {
			auto it = lower_bound(v.begin() + i, v.end(), v[i] + 2);
			if (it != v.end()) swap(*it, v[i + 1]);
			else {
				auto ub = upper_bound(v.begin() + i + 1, v.end(), v[i]);
				auto lb = lower_bound(v.begin() + i - cnt, v.end(), v[i]);
				while (ub != v.end()) {
					swap(*lb, *ub);
					lb++; ub++;
				}
			}
			cnt = 0;
		}
		else if (v[i + 1] == v[i]) cnt++;
	}
	for (auto i : v) cout << i << ' ';
}