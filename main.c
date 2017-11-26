#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "parse_execute.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

int main(char * args[]){
    char cwd[1024]; //current working directory
    getcwd(cwd,sizeof(cwd));
    printf(GRN "cwd:" CYN "~%s" RESET "$", cwd);
    get_and_execute();
    return 0;
}