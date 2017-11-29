#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "redirect.h"

char ** parse_args( char * line ) {
  char ** a = (char **)calloc(25, sizeof(char[256]));
  int index = 0;
  char * newline = strchr(line, '\n');
  if (newline)
    *newline = 0;
  while (line[0] == ' ')
    line++;
  int end_index = strlen(line)-1;
  while (line[end_index] == ' ') {
    line[end_index] = 0;
    end_index--;
  }
    
  while (line) {
    a[index] = strsep(&line, " ;");
    if (!strchr(a[index], ' ')) {
      index++;
    }
  }
  a[index] = NULL;
  return a;
}

void get_and_execute() {
  char *line;
  line = (char *) malloc(256 * sizeof(char));
  fgets(line, 256, stdin);

  //checking for semicolons
  char *semi_line;
  semi_line = (char *) malloc(256 * sizeof(char));
  char ** args;
  int child;
	
  while ((semi_line = strsep(&line, ";")) != NULL) {
    args = parse_args(semi_line);

    int i = 0;
    while(args[++i]){}//i-1 is the index of the last argument

    child = fork();	  
    ////////////////////////child
    if(!child){
      //CHILD PROCESS
      //takes & token out for execution
      if(!strcmp(args[i-1], "&"))
	args[i-1] = NULL;

      //exits if commands are exit/cd (parent responsible)
      if(!strcmp(args[0],"exit") || !strcmp(args[0], "cd"))
	exit(0);
      //redirects left
      else if((i ==3) && !strcmp(args[1], ">"))
        redirect_left(args[0],args[2]);
      //if regular program than execute it
      execvp(args[0], args);
      exit(0);
    }

    /////////////////////////parent
    else{
      //PARENT PROCESS
      //waits for child to finish if & token is absent
      if(strcmp(args[i-1], "&")){
	int *status;
	wait(status);
      }

      //addresses exit/cd/> commands
      if(!strcmp(args[0],"exit"))
	exit(0);
      if(!strcmp(args[0],"cd"))
	chdir(args[1]);      
    }
  }
  return;

}
