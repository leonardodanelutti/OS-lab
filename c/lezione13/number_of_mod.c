#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h> 

int main(int argc, char **argv)
{
  if(argc != 3) {
    fprintf(stderr, "Inserire il percorso di un file e il numero di secondi.\n");
    return 1;
  }

  char *file = argv[1];
  int sec = atoi(argv[2]);

  struct stat sb;
  if(stat(file, &sb) == -1)
  {
    fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
            argv[0], file, strerror(errno));
    return 1;
  }
  
  int n = 1;

  time_t mtime = sb.st_mtime;
  time_t start = time(NULL);

  while(start + sec > time(NULL)) {
    if(stat(file, &sb) == -1)
    {
      fprintf(stderr, "%s: errore nell'accesso al file %s: %s\n",
              argv[0], file, strerror(errno));
      return 1;
    }

    if(sb.st_mtime != mtime) {
      printf("Il file %s è stato modificato %d volte;\n", file, n);
      mtime = sb.st_mtime;
      n++;
    }

    sleep(1);
  }
  return 0;
}
