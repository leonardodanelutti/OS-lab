#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

struct stat sb;

int main(int argc, char **argv) {

	for (int i = 1; i < argc; i++) {
	
		int fd = open(argv[i], O_RDONLY);
		
		if (fstat(fd, &sb) == -1) {
			fprintf(stderr, "%s: errore nell’accesso al file: %s\n",
			argv[0], strerror(errno));
			return 1;
		}
		
		int *tmp = malloc(sb.st_size);
		
		if (read(fd, tmp, sb.st_size) == -1) {
			fprintf(stderr, "%s: errore nella lettura del file: %s\n",
			argv[0], strerror(errno));
			return 1;
		}
		
		close(fd);
		
		if (write(1, tmp, sb.st_size) == -1) {
			fprintf(stderr, "%s: errore nella scrittura allo stdout: %s\n",
			argv[0], strerror(errno));
			return 1;
		}
		
		free(tmp);
		
		printf("\n");
		
	}
	return 0;
}


