#include <stdio.h>

int lg(int);

int lg(int n) {

	if (n < 1) {
		return -1;
	}

	int m = 0;
	int pow = 1;

	while (pow <= n) {
		m++;
		pow = pow * 10;
	}

	return m-1;
}

int main() {
	int n;
	scanf("%d", &n);
	int m = lg(n);
	printf("%d \n", m);
	return 0;
}
