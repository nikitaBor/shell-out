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
  char *line;
  line = (char *) malloc(256 * sizeof(char));
  fgets(line, 256, stdin);
  /*printf("fgot\n");
  
  //checking for semicolons
  char *semi_line;
  semi_line = (char *) malloc(256 * sizeof(char));
  int forker;
  while ((semi_line = strsep(&line, ";")) != NULL) {
    printf("forked\n");
    forker = fork();
    if (!forker) {
      break;
    }
  }
  
  printf("semi_line: %s\n", semi_line);
  if (!semi_line[0])
    return;
  */
  char ** args = parse_args(/*semi_*/line);
  //printf("parsed\n");

  
  int i = 0;
  while(args[++i]){}//i-1 is the index of the last argument

  int child;
  while ((semi_line = strsep(&line, ";")) != NULL) {
    child = fork();
    if(!child){
      //CHILD PROCESS
      //takes & token out for execution
      if(!strcmp(args[i-1], "&"))
	args[i-1] = NULL;

      //returns if commands are exit/cd (parent responsible)
      if(!strcmp(args[0],"exit") || !strcmp(args[0], "cd"))
	exit(0);

      execvp(args[0], args);
    }
    else{
      //PARENT PROCESS
      //waits for child to finish if & token is absent
      if(strcmp(args[i-1], "&")){
	int *status;
	wait(status);
      }

      //addresses exit/cd commands
      if(!strcmp(args[0],"exit")){
	exit(0);
      }
      if(!strcmp(args[0],"cd")){
	chdir(args[1]);
      }
    }
    return;
    //execlp("./shell_out", "next_run", NULL); //reruns itself
  }
}
