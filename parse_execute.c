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

  int i = 0;
  while(args[++i]){}//i-1 is the index of the last argument

  int child = fork();
  if(!child){ //child
    if(*args[i-1] == '&')
      args[i-1] = NULL;
    execvp(args[0], args);
    return;
  }
  else{
    if(*args[i-1] != '&'){
      int *status;
      wait(status);
    }
    execlp("./shell_out", "next_run", NULL); //reruns itself
  }
}
