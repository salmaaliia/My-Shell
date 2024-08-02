#include <stdio.h>
#include <fcntl.h>
#include "mymv.h"

void runMymv(int argcnt, char ** args)
{
	if(argcnt != 3)
	{
                perror("To use mymv: mymv <source> <dist>");
                return;
        }

	if(rename(args[1], args[2]) != 0)
	{
		printf("Error moving file");
		return;
	}
	

}
