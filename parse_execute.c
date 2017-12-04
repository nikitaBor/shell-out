#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "redirect.h"
#include "parse_execute.h"

/*======== char ** parse_args() ==========
Inputs: char *line
Returns: a char** populated with arguments that were seperated by spaces

Removes whitespace from beginning and end of input line and splits the line into strings along whitespace
====================*/
char ** parse_args(char *line){
  char **a = (char **) calloc(25, sizeof(char[256]));
  int index = 0;
  char *newline = strchr(line, '\n');
  if (newline)
    *newline = 0;
  int end_index = strlen(line) - 1;
  while (line[end_index] == ' ') {
    line[end_index] = 0;
    end_index--;
  }

  while (line) {
    while (line[0] == ' ')
    line++;
    a[index] = strsep(&line, " ;");
    if (!strchr(a[index], ' ')) {
      index++;
    }
  }
  a[index] = NULL;
  return a;
}


/*======== void get_and_execute() ==========
Inputs: none
Returns: void

Gets user inputed command w/ fgets, parses it using parse_args, and executes it by forking off a child process
When semicolons appear in the input, get_and_execute() parses executes each side separately
When < or > appear, references appropriate function from redirect.c to execute properly
====================*/
void get_and_execute() {
  char *line;
  line = (char *) malloc(256 * sizeof(char));
  fgets(line, 256, stdin);

  //checking for semicolons
  char *semi_line;
  char *left_line;
  //    semi_line = (char *) malloc(256 * sizeof(char));
  char **args;
  char **left_args; //arguments left of >/<
  int redirectCond = 0; //1 for >, -1 for <, 2 for |, 0 for no >/</|
  int i; //will be used as counter for number of arguments
  int child;

  while ((semi_line = strsep(&line, ";")) != NULL) {
    if (strchr(semi_line, '>') != NULL) {
      left_line = strsep(&semi_line, ">");
      left_args = parse_args(left_line);
      redirectCond = 1;
    }
    else if(strchr(semi_line, '<') != NULL) {
      left_line = strsep(&semi_line, "<");
      left_args = parse_args(left_line);
      redirectCond = -1;
    }
    else if(strchr(semi_line, '|') != NULL) {
        left_line = strsep(&semi_line, "|");
        left_args = parse_args(left_line);
        redirectCond = 2;
    }
    args = parse_args(semi_line);

    i = 0;
    while (args[++i]) {}//i-1 is the index of the last argument


    child = fork();
    ////////////////////////child
    if (!child) {
      //CHILD PROCESS
      //takes & token out for execution
      if (!strcmp(args[i - 1], "&"))
	args[i - 1] = NULL;

      //exits if commands are exit/cd/>/</| (parent responsible)
      if (!strcmp(args[0], "exit") || !strcmp(args[0], "cd") || redirectCond) {
          exit(0);
      }
      //if regular program than execute it
      execvp(args[0], args);
      exit(0);
    }
    /////////////////////////parent
    else {
      //PARENT PROCESS
      //waits for child to finish if & token is absent
      if (strcmp(args[i - 1], "&")) {
	int status;
	wait(&status);
      }

      //addresses exit/cd/>/</| commands
      if (redirectCond == 1){
	redirect_left(left_args,args);
      }
      else if(redirectCond == -1){
	redirect_right(left_args, args);
      }
      else if(redirectCond == 2){
          redirect_pipe(left_args, args);
      }
      else if (!strcmp(args[0], "exit"))
	exit(0);
      else if (!strcmp(args[0], "cd"))
	chdir(args[1]);
    }
  }
  return;
}
