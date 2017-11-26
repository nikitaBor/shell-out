#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char ** parse_args( char * line ) {
  char ** a = (char **)calloc(25, sizeof(char[256]));
  int index = 0;
  while (*line) {
    a[index] = strsep(&line, " \n");
    index++;
  }
  a[index] = NULL;
  return a;
}

void get_and_execute() {
  char line[256];
  fgets(line, sizeof(line), stdin);
  char ** args = parse_args(line);

  int child = fork();
  if(!child){ //child
    execvp(args[0], args);
    return;
  }
  else{
    int *status;
    wait(status);
    execlp("./shell_out", "next_run", NULL); //reruns itself but with new args
  }
}
