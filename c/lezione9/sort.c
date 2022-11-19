#include <stdio.h>

void sort(int *array, int size) {
	for (int i = 1; i < size; i++){
		int value = array[i];
		int j = i - 1;		
		while (j >= 0 && array[j] > value) {
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = value;
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
	
	sort(array, size);
	
	printf("Array ordinato:\n");
	for(int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
