#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {

	char *name = "/dev/urandom";
	FILE *file = fopen(name, "rb");
	int n[10];
	fread(n, sizeof(int), 10, file);
	
	for (int i = 0; i < 10; i++) {
		printf("%d\n", n[i]);
	}
	fclose(file);
	
	return 0;
}
