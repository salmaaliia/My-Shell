#include <stdio.h>
#include <string.h>
#include "myecho.h"

void runMyecho(int argcnt, char **args) {

    if (args != NULL) 
    {
       for(int i = 1; i < argcnt; i++)
       {
	       printf("%s ", args[i]);
       }

    } 
}

