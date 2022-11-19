#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("Utilizzo del comando: %s <file>", argv[0]);
		return 1;
	}
	
	char *filename = argv[1];
	
	int file = open(filename, O_RDONLY);
	
	if(!file) {
		fprintf(stderr, "Errore nell’apertura del file!\n");
		return 2;
	}
	
	int pipes[2] = { };
	if(pipe(pipes) == -1) {
		perror("pipe()");
		return 1;
  	}
  	
  	pid_t ls = fork();
  	switch(ls) {
    		case -1:
      			perror("fork()");
      			exit(2);
    		case 0: // figlio
      			dup2(file, 1); // redirigo stdout
      			close(pipes[1]);
      			execlp("ls", "ls", "-l", NULL);
      			perror("ls"); // se arrivo qui, execlp() ha fallito
      			return 2;
  	} // il padre prosegue
  	
  	
	
}
