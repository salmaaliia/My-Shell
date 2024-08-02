#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "envir.h"

extern char ** environ;

void runMyenvir(int argcnt, char **args)
{
	if(argcnt == 1)
	{
		for(int i = 0; environ[i] != NULL; i++)
		{
	 		printf("environ[%d] = %s\n", i, environ[i]);
		}

	}
	else if (argcnt == 2) {
		const char *value = getenv(args[1]);
		if (value != NULL) {
		       	printf("%s=%s\n", args[1], value);
		} else {
		       	printf("Variable %s not found.\n", args[1]);
		}
        }

}
