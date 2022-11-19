
#include <stdio.h>

#define LEN 10

int main() {
	int a[LEN] = {4, 8, 2, 0, 5, 6, 3, 9, 1, 7};
	for (int i = 1; i < LEN; i++) {
		int value = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > value) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = value;
	}

	for(int i = 0; i < LEN; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
