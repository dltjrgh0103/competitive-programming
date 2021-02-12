#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	int n0 = n, count = 0;
	while (count == 0 || n0 != n) {
		int f = n / 10;
		int b = n % 10;
		int nf = (f + b) % 10;
		int ret = (b * 10) + nf;
		n = ret;
		count++;
	}

	cout << count << endl;
	return 0;
}