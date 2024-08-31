#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "external.h"

void runExternal(char **args)
{
    pid_t pid = fork();

    if (pid == -1) {
	    perror("Fork failed");
	    exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
    	    if (execvp(args[0], args) == -1) {
		    perror("Execution failed");
		    exit(EXIT_FAILURE);
	    }
    } 
    else {
    	    int status;
    	    if (waitpid(pid, &status, 0) == -1) {
		    perror("Waitpid failed");
    	    } 
     	    else {
		    if (WIFEXITED(status)) {
	    		    int exitStatus = WEXITSTATUS(status);
	    		    if (exitStatus != 0) {
				    printf("Command exited with non-zero status: %d\n", exitStatus);
			    }
            } 
            else if (WIFSIGNALED(status)) {
    		    printf("Command terminated by signal: %d\n", WTERMSIG(status));
            }
        }
    }
}

