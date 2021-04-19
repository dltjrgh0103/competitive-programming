#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;

int main(void) {
    int a, b;

    scanf("%d %d", &a, &b);
    bool* arr = new bool[b + 1];

    for (int i = 0; i < b + 1; i++) {
        arr[i] = true;
    }

    int j;
    for (int i = 2; i < b + 1; i++) {
        if (arr[i]) {
            if ((unsigned int)pow(i, 2) > 1000001) break;
            else {
                for (j = (int)pow(i, 2); j < b + 1;) {
                    arr[j] = false; j = j + i;
                }
            }
        }
    }

    if (a == 1) a++;

    for (int i = a; i < b + 1; i++) if (arr[i] && i >= a) printf("%d\n", i);

    delete[]arr;
    return 0;
}