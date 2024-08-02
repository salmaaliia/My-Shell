#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mypwd.h"

#define SIZE 1024

void runMypwd()
{
	char buf[SIZE];

	if(getcwd(buf, sizeof(buf)) != NULL)
	{
		printf("%s", buf);
	}
	else{
	       perror("getcwd() error");
	}
}	
