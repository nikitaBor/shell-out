#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

void redirect_left(char** source, char* target){
  int fd = open(target,O_WRONLY);
  int stdout_placeholder = dup(1);
  dup2(fd, 1);
  int forker = fork();
  printf("forked haha\n");
  if(!forker) {//child-of-child
    printf("child\n");
    printf("source[0]: %s\n", source[0]);
    printf("source[1]: %s\n", source[1]); 
    execvp(source[0], source);
  }
    
  else {
    int *status;
    wait(status);
    dup2(stdout_placeholder, 1);
  }
  exit(0);
}
