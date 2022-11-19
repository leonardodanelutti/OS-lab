#include <stdio.h>

int main() {

	long nc = 0;

	for(char c = getchar(); c!=EOF; c = getchar()) {
		if (c == ' ' || c == '\n' || c == '\t')  {
			nc++;
		}
	}
	printf("Number of whitespace characters: %ld\n", nc);
	return 0;
}
