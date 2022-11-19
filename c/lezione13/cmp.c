#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_SIZE 10000

int str_equal(char *str1, char *str2) {

	for (int i = 0; str1[i] || str2[i]; i++) {
		if (str1[i] != str2[i]) {
			return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv) {

	if(argc != 3) {
		fprintf(stderr, "Fornire due file\n");
		return 1;
	}
	
	char *filename1 = argv[1];
	char *filename2 = argv[2];

	FILE *file1 = fopen(filename1, "r");
	FILE *file2 = fopen(filename2, "r");
	if(!file1 || !file2) {
		fprintf(stderr, "Errore nell’apertura del file!\n");
		return 2;
	}
	
	char *tmp1 = calloc(MAX_LINE_SIZE, sizeof(char));
	char *tmp2 = calloc(MAX_LINE_SIZE, sizeof(char));	
	
	int n = 0;
	
	char *s1 = fgets(tmp1, MAX_LINE_SIZE, file1);
	char *s2 = fgets(tmp2, MAX_LINE_SIZE, file2);
	
	while (s1 != NULL || s2 != NULL) {
		
		if (!str_equal(tmp1, tmp2)) {
			printf("line: %d\n", n);
			fprintf(stdout, "%s: %s\n", argv[1], tmp1);
			fprintf(stdout, "%s: %s\n", argv[2], tmp2);
			return 0;
		}
		n++;
		free(tmp1);
		free(tmp2);
		char *tmp1 = calloc(MAX_LINE_SIZE, sizeof(char));
		char *tmp2 = calloc(MAX_LINE_SIZE, sizeof(char));
		s1 = fgets(tmp1, MAX_LINE_SIZE, file1);
		s2 = fgets(tmp2, MAX_LINE_SIZE, file2);
		
	}
	
	free(tmp1);
	free(tmp2);
	fclose(file1);
	fclose(file2);
	
	printf("No matches\n");
	return 0;

}
