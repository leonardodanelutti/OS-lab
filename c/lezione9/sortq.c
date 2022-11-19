#include <stdio.h>


void copy(int *array_to_be_copied, int *array_overwritten, int a, int b) {
	for (int i = a; i<=b; i++) {
		array_overwritten[i] = array_to_be_copied[i-a];
	}
}

void merge(int *array, int size, int a, int b, int c) {
	
	int ordered_array[size];
	int i = a;
	int j = c+1;
	int k = 0;

	while (i<=c && j<=b) {
		if (array[i] > array[j]){
			ordered_array[k] = array[j];
			j++;
		} else {
			ordered_array[k] = array[i];
			i++;
		}
		k++;
	}
	
	while (i<=c) {
		ordered_array[k] = array[i];
		i++;
		k++;
	}

	while (j<=b) {
		ordered_array[k] = array[j];
		j++;
		k++;
	}
	
	copy(ordered_array, array, a, b);
}

void sortq(int *array, int size, int a, int b) {
	if (a < b) {
		int c = (a + b) / 2;
		sortq(array, size, a, c);
		sortq(array, size, c+1, b);
		merge(array, size, a, b, c);
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
	
	sortq(array, size);
	
	printf("Array ordinato:\n");
	for(int i = 0; i < size; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}
