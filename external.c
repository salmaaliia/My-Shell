#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "external.h"

void renExternal(char **args)
{
	pid_t pid = fork(); 
       
	if (pid == -1)
       	{
	       	printf("\nFork Fail");
		return;
       	}
       	else if (pid == 0)
       	{
		if (execvp(args[0], args) < 0)
	       	{
	     		printf("\nCommand cannot be excuted");
	       	}
		exit(0);
       	}
       	else {
		int stat;
	       	wait(&stat); 
	      	return;
       	}
}
