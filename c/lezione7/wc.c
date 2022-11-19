#include <stdio.h>

int main() {

	int previousWhite = 0;
	long wc = 0;

	for(char c = getchar(); c!=EOF; c = getchar()) {
		if ((c == ' ' || c == '\n' || c == '\t') && !previousWhite) {
			previousWhite = 1;
			wc++;
		} else if (c != ' ' && c != '\n' && c != '\t') {
			previousWhite = 0;
		}
	}
	
	printf("Number of words: %ld\n", wc);
	
	return 0;
}
