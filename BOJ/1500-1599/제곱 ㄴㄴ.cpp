#include<stdio.h>
using namespace std;
const int SZ = 40559;
int k, len = 0, p[SZ], s[SZ];
int func(int x)
{
	int ret = 0, i = 0;
	while (s[i] <= x)	ret += x / s[i++];
	return x - ret;
}
int main(void) {
	scanf("%d", &k);
	for (int i = 2; i < SZ; i++)
	{
		if (p[i]) continue;
		for (int j = i; j < SZ; j += i)
		{
			if (j % (i * i) == 0) p[j] = -SZ;
			else p[j]++;
		}
	}
	for (int i = 2; i < SZ; i++)
		if (p[i] > 0) s[len++] = (p[i] % 2 ? 1 : -1) * i * i;

	int ans = k, sum = -1;
	while (k - sum)
	{
		sum = func(ans);
		ans += (k - sum);
	}
	printf("%d", ans);
	return 0;
}