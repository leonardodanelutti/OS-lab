#include <stdio.h>

int main() {
	int x;
	int y;
	int sum = 0;
	while (y != EOF) {
		sum = sum + x;
		y = scanf("%d", &x);
	}
	printf("Somma: %d\n", sum);
}
