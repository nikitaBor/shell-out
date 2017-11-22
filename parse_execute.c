#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char ** parse_args( char * line ) {
  char ** a = (char **)calloc(25, sizeof(char[256]));
  int index = 0;
  while (line) {
    a[index] = strsep(&line, " ");
    index++;
  }
  a[index-1] = NULL;
  return a;
}

void get_and_execute() {
  char line[256];
  fgets(line, sizeof(line), stdin);
  char ** args = parse_args(line);
  execvp(args[0], args);
}
