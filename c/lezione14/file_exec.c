#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_LINE_SIZE 10000

int read_line (FILE *file, char *s) {

	int i = 0;
	for (char c = fgetc(file); c != '\n'; c = fgetc(file)) {
		if (c == EOF) {
			return -1;
		} else {
			s[i] = c;
			i++;
		}
	}
	return i;
}

int find (char **argv, int argc) {
	for (int i = 3; i < argc; i++) {
		if (argv[i][0] == '@') {
			return i;
		}
	}
	return 0;
}

int main(int argc, char **argv) {

	if (argc < 4) {
		fprintf(stderr, "Fornire un file e un comando\n");
		return 1;
	}
	
	char *filename = argv[1];
	
	FILE *file = fopen(filename, "r");
	
	if(!file) {
		fprintf(stderr, "Errore nell’apertura del file!\n");
		return 2;
	}
	
	char *line = calloc(MAX_LINE_SIZE, sizeof(char));
	int size = read_line(file, line);
	line = realloc(line, size);
	int pos = find(argv, argc);
	argv[pos] = line;
	
	if (pos) {
		while (size != -1) {
					
			pid_t pid = fork();
			
			switch (pid) {
				case -1:
					perror("fork() failed");
					return 3;
				case 0:
					execvp(argv[2], argv + 2);
					perror("exec failed");
					return 4;	
			}
			wait(NULL);
			char *line = calloc(MAX_LINE_SIZE, sizeof(char));
			size = read_line(file, line);
			line = realloc(line, size);
			argv[pos] = line;
			
		}
	} else {
		execvp(argv[2], argv + 2);
	}
	return 0;
}
