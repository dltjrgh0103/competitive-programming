#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	int num;
	int f = 0, s = 1;
	if (n == 0) num = 0;
	else {
		while (n--) {
			int nf = s;
			int ns = f + s;
			num = nf;
			f = nf; s = ns;
		}
	}

	cout << num << endl;
	return 0;
}