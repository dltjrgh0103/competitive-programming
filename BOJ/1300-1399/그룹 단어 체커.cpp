#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	int count = 0;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		bool check = true;

		for (int j = 0; j < s.length(); j++) {
			for (int k = 0; k < j; k++) {
				if (s[j] != s[j - 1] && s[j] == s[k]) {
					check = false; break;
				}
			}
		}
		if (check) count++;
	}

	cout << count;
	return 0;
}