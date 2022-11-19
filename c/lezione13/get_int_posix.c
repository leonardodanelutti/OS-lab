#include <stdio.h>
#include <unistd.h>

int main() {
	char *name = "/dev/urandom";
	int fd = open(name, O_RONLY);
	int n[10];
	read(fd, n, 10*sizeof(int));
	for (int i = 0; i < 10; i++) {
		printf("%d\n", n[i]);
	}
	
	close(file);
	
	return 0;
	
}
