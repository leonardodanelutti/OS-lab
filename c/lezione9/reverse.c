#include <stdio.h>

void swap(int *array, int a, int b) {
	int tmp = array[a];
	array[a] = array[b];
	array[b] = tmp;
}

void reverse(int *array, int size) {
	for (int i = 0; i < size / 2; i++) {
		swap(array, i, size-1-i);
	}
}

int main() {
	int x;
	int size;
	int i = 0;
	
	printf("Inserisci il numero di elementi:\n");
	scanf("%d", &size);
	
	int array[size];
	
	printf("Inserisci gli elementi:\n");
	while (i < size) {
		scanf("%d", &x);
		array[i] = x;
		i++;
	}
	
	reverse(array, size);
	
	printf("Array ordinato:\n");
	for(int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
