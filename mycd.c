#include <stdio.h>
#include <unistd.h>
#include "mycd.h"

void runMycd(int argcnt, char **args)
{
	if(argcnt != 2)
	{
		perror("To use mycd: mycd <Path>");
	}
	else if(chdir(args[1]) != 0)
	{
		perror("chdir() error");
	}

}
