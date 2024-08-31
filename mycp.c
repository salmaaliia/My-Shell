#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mycp.h"

void runMycp(int argcnt, char **args)
{

	if(argcnt != 3)
	{
		perror("To use mycp: mycp <source> <dist>");
		return;
	}

	char buf[100];

	int sourceFD = open(args[1], O_RDONLY);
	if(sourceFD == -1)
	{
		perror("Error! cannot open source file");
		return;
	}

	int destFD = open(args[2], O_WRONLY | O_CREAT, 0644);
        if(destFD == -1)
        {
                perror("Error! cannot open destination file");
		close(sourceFD);
	  	return;
        }

	int count;
	while((count = read(sourceFD, buf, sizeof(buf))) > 0)
	{
		if(write(destFD, buf, count) != count)
		{
		        perror("Error writing to destination file");
                        close(sourceFD);
			close(destFD);
                        return;
		}

	}

	if(count == -1)
        {
          	 perror("Error reading from source file");
                 close(sourceFD);
                 close(destFD);
 		 return;
        }


	close(sourceFD);
        close(destFD);

}
