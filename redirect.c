#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


/*======== int openFileForWrite() ==========
Inputs: char *targetName
Returns: the file directory of the file opened

Opens for writing a file with its name as the inputted targetName
====================*/
int openFileForWrite(char *targetName) {
    int fd = open(targetName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        fprintf(stderr, "Cannot open file %s\n", targetName);
    }
    return fd;
}


/*======== int openFileForRead() ==========
Inputs: char *sourceName
Returns: the file directory of the file opened

Opens for reading a file with its name as the inputted sourceName
====================*/
int openFileForRead(char *sourceName){
    int fd = open(sourceName, O_RDONLY);
    if(fd == -1){
        fprintf(stderr, "Cannot open file %s\n", sourceName);
    }
    return fd;
}


/*======== void redirect_left() ==========
Inputs: char **source, char **target
Returns: void

Writes into the target file with the stdout from executing the source commands
====================*/
void redirect_left(char **source, char **target) {
    int fd = openFileForWrite(target[0]);
    if(fd == -1)
        return;

    int stdout_placeholder = dup(1);
    dup2(fd, 1);
    if (!fork()) { //child
        execvp(source[0], source);
    }
    else { //parent
        int status;
        wait(&status);
        dup2(stdout_placeholder, 1);
    }
    close(fd);
    return;
}


/*======== void redirect_right() ==========
Inputs: char **target, char **source
Returns: void

Uses the source file for stdin when executing the target commands
====================*/
void redirect_right(char **target, char **source){
    int fd = openFileForRead(source[0]);
    if(fd == -1)
        return;

    int stdin_placeholder = dup(0);
    dup2(fd, 0);
    if(!fork()){ //child
        execvp(target[0], target);
    }
    else{ //parent
        int status;
        wait(&status);
        dup2(stdin_placeholder, 0);
    }
    close(fd);
    return;
}


/*======== void redirect_pipe() ==========
Inputs: char **source, char **target
Returns: void

Runs the source and uses its output as the input when running target
====================*/
void redirect_pipe(char **source, char** target){
    char** dummy = calloc(1, sizeof(char[256]));
    dummy[0] = "dummyFileForRedirectPipe.txt";
    redirect_left(source,dummy);
    redirect_right(target, dummy);
    free(dummy);
    return;
}


