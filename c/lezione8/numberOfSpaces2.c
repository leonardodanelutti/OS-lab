#include <stdio.h>

int is_whitespace(char);

int is_whitespace(char c) {
	return c == ' ' || c == '\n' || c == '\t';
}

int main() {

	int previousWhite = 0;

	for(char c = getchar(); c!=EOF; c = getchar()) {
		if (is_whitespace(c) && !previousWhite) {
			printf("\n");
			previousWhite = 1;
		} else if (! is_whitespace(c)) {
			previousWhite = 0;
			printf("-");
		}
	}
	return 0;
}
