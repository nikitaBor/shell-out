# shell-out
Features:
	Forks and executes commands, through all whitespace(between command words and ;).
	Parses multiple commands on one line(seperated by ;).
	Redirects using >, <.
	Handles |.

Attempted:
	Being able to handle '&' token (partially works but with bug)

Bugs:
	*If a program is called with the '&' token, shell-out will continue running fine with this program in the background
	  until the program is closed. After the program in the background stops running, shell-out will no longer wait 
	  for any commands to finish running (asking for further user input before other programs ran)
	* Has problems with executing some | commands (cat | ls will execute both cat and ls) particularly when the right
	   arguments do not take in input(like ls).
	

Files & Function Headers:
main.c

  	/*======== int main() ==========
    Inputs: char * args[]
    Returns: nothing
    
    Gets the current working directory and prints it on the input line
    Runs an infinite while loop of get_and_execute from parse_execute.c
    ====================*/

parse_execute.c

  	/*======== char ** parse_args() ==========
    Inputs: char *line
    Returns: a char** populated with arguments that were seperated by spaces
    
    Removes whitespace from beginning and end of input line and splits the line into strings along whitespace
    ====================*/

  	/*======== void get_and_execute() ==========
    Inputs: none
    Returns: void
    
    Gets user inputed command w/ fgets, parses it using parse_args, and executes it by forking off a child process
    When semicolons appear in the input, get_and_execute() parses executes each side separately
    When < or > appear, references appropriate function from redirect.c to execute properly
    ====================*/

redirect.c

  	/*======== int openFileForWrite() ==========
    Inputs: char *targetName
    Returns: the file directory of the file opened
    
    Opens for writing a file with its name as the inputted targetName
    ====================*/
    
    /*======== int openFileForRead() ==========
    Inputs: char *sourceName
    Returns: the file directory of the file opened
    
    Opens for reading a file with its name as the inputted sourceName
    ====================*/
    
    /*======== void redirect_left() ==========
    Inputs: char **source, char **target
    Returns: void
    
    Writes into the target file with the stdout from executing the source commands
    ====================*/

    /*======== void redirect_right() ==========
    Inputs: char **target, char **source
    Returns: void
    
    Uses the source file for stdin when executing the target commands
    ====================*/
    
    /*======== void redirect_pipe() ==========
    Inputs: char **source, char **target
    Returns: void

    Runs the source and uses its output as the input when running target
    ====================*/
