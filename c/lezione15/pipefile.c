#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINE_SIZE 10000

int read_line(int file, char *s) {

    int i = 0;
    char c;
    for (int l = read(file, &c, 1); c != '\n'; l = read(file, &c, 1)) {
        if (c == EOF) {
            return -1;
        } else {
            s[i] = c;
            i++;
        }
    }

    if (i != 0)
        s[i] = '\n';

    return i;
}

int to_arr(char *s, int size, char **buffer) {

    int k = 0;
    int j = 0;
    char *str = malloc(MAX_LINE_SIZE);

    for (int i = 0; i <= size; i++) {
        if (s[i] == '\n') {
            str = realloc(str, j+1);
            buffer[k] = str;
            buffer[k+1] = NULL;
            k += 2;
            break;
        } else if (s[i] == ' ') {
            str = realloc(str, j);
            buffer[k] = str;
            str = malloc(MAX_LINE_SIZE);
            k++;
            j = 0;
        } else {
            str[j] = s[i];
            j++;
        }
    }
    return k;
}

int read_arr(int file, char **buffer) {
    char *s = malloc(MAX_LINE_SIZE);
    int line_size = read_line(file, s);
    if (line_size == -1) {
        free(s);
        return line_size;
    }
    s = realloc(s, line_size);
    int arr_size = to_arr(s, line_size, buffer);
    free(s);
    return arr_size;
}

int find(char **arr) {
    int i = 0;
    while (strncmp(arr[i], "|", MAX_LINE_SIZE) != 0) {
        i++;
    }
    return i;
}

int exec(char **arr) {
    int i = find(arr);
    arr[i] = NULL;
    
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
      dup2(pipes[1], 1); // redirigo stdout
      close(pipes[0]);
      execvp(arr[0], arr);
      perror("ls"); // se arrivo qui, execlp() ha fallito
      return 2;
  } // il padre prosegue

  pid_t grep = fork();
  switch(grep) {
    case -1:
      perror("fork()");
      exit(2);
    case 0: // figlio
      close(pipes[1]);
      dup2(pipes[0], 0); // redirigo stdin
      execvp(arr[i+1], arr+i+1);
      perror("grep"); // se arrivo qui, execlp() ha fallito
  } // il padre prosegue

  close(pipes[0]);
  close(pipes[1]);
  // aspetto entrambi i figli
  waitpid(ls,NULL,0);
  waitpid(grep,NULL,0);
    return 4;
}


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Utilizzo del comando: %s <file>", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    int file = open(filename, O_RDONLY);

    if(file == -1) {
        fprintf(stderr, "Errore nell’apertura del file!\n");
        return 2;
    }

    char **arr = malloc(MAX_LINE_SIZE * sizeof(char *));
    int arr_size = read_arr(file, arr);

    while (arr_size != -1) {
        arr = realloc(arr, arr_size * sizeof(char *));
        fprintf(stdout,"arg: %s\n", arr[3]);
        printf("forking\n");

        pid_t pid = fork();

        switch (pid) {
            case -1:
                perror("fork() failed");
                return 3;
            case 0:
            	fprintf(stdout, "figlio1!\n");
                return exec(arr);
        }
	
	wait(NULL);
	fprintf(stdout, "padre1!\n");
        arr = malloc(MAX_LINE_SIZE * sizeof(char *));
        int arr_size = read_arr(file, arr);
    }
    return 0;
}
