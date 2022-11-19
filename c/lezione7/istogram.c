#include <stdio.h>

int main() {

	int previousWhite = 0;

	for(char c = getchar(); c!=EOF; c = getchar()) {
		if ((c == ' ' || c == '\n' || c == '\t') && !previousWhite) {
			printf("\n");
			previousWhite = 1;
		} else if (c != ' ' && c != '\n' && c != '\t') {
			previousWhite = 0;
			printf("-");
		}
	}
	return 0;
}
