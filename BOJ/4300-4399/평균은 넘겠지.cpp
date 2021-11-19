#include <iostream>

using namespace std;

void func();

int main(int argc, const char* argv[]) {

	int C;
	cin >> C; // test case

	for (int i = 0; i < C; i++) {
		func();
	}

	return 0;
}

void func() {
	int N;
	cin >> N;

	// ���� �迭 ���� �� ����
	int* arr = new int[N]; // Ȥ�� int* arr = (int*)malloc(sizeOf(int) * size)

	for (int i = 0; i < N; i++) {
		cin >> arr[i]; // i ~ N - 1 ���� �Է¹��� ��ҷ� �ʱ�ȭ
	}

	// ��� ���ϱ�
	double avg = 0;
	for (int i = 0; i < N; i++) {
		avg += arr[i]; // ��� ���� ������
	}
	avg = avg / N; // �����տ� ���� N���� ������.

	// ��� ������ �Ѵ� �ο� �� ���ϱ�
	double count = 0;
	for (int i = 0; i < N; i++) {
		if (arr[i] > avg) {
			count++;
		}
	}

	// ����� �Ѵ� �ο� %
	double result = (count / N) * 100;
	cout << fixed;
	cout.precision(3);
	cout << result << "%\n";

	delete[] arr; // ���� �Ҵ��� �� ��쿡�� ���̻� �Ⱦ��� ��� �ݵ�� �޸� ������ �ؾ��Ѵ�.
}

// 20.01.17 Andrew Lee (dltjrgh)