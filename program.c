#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "mycp.h"
#include "mymv.h"
#include "mypwd.h"
#include "myecho.h"
#include "myhelp.h"
#include "mycd.h"
#include "envir.h"
#include "external.h"
#include "mytype.h"

#define MAXARG 150

void currentDir()
{
	char*  user;
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	user = getenv("USER");
	printf("\n$%s:~%s$", user, cwd); 
}

int takeCommand(char *cmd)
{
	char* str;
	str = readline(" >> ");
	
	if(strlen(str) != 0)
	{
		strcpy(cmd, str);
		free(str);
		return 0;
	}
	else {
		free(str);
		return 1;
	}

}

int  parceCommand(char *cmd, char ** parsed)
{
	int i = 0;
	while(i < MAXARG)
	{
		parsed[i] = strsep(&cmd, " ");

		if(parsed[i] == NULL) 
			break;
		if(strlen(parsed[i]) != 0)
			i++;
	}
	return i;
}

void terminateCommand(int sz, char *parsedCmd[])
{
	if(strcmp(parsedCmd[0], "mycp") == 0)
	{
		runMycp(sz, parsedCmd);
	}
	else if(strcmp(parsedCmd[0], "mymv") == 0)
	{
		runMymv(sz, parsedCmd);
	}
	else if(strcmp(parsedCmd[0], "mypwd") == 0)
	{
		runMypwd();
	}
	else if(strcmp(parsedCmd[0], "myecho") == 0)
	{
		runMyecho(sz, parsedCmd);
	}
	else if(strcmp(parsedCmd[0], "myexit") == 0)
	{
		exit(0);
	}
	else if(strcmp(parsedCmd[0], "myhelp") == 0)
	{
		runMyhelp(sz, parsedCmd);
	}
	else if(strcmp(parsedCmd[0], "mycd") == 0)
	{
		runMycd(sz, parsedCmd);
	}
	else if(strcmp(parsedCmd[0], "envir") == 0)
	{
		runMyenvir(sz, parsedCmd);
	}
        else if(strcmp(parsedCmd[0], "mytype") == 0)
        {
	       	runMytype(parsedCmd);
        }
	else {
		renExternal(parsedCmd);
	}




}
int main()
{
	char cmd[1024], *parsedCmd[MAXARG];

	while(1)
	{
		currentDir();

		if(takeCommand(cmd) == 1) continue;

		int sz = parceCommand(cmd, parsedCmd);

		terminateCommand(sz, parsedCmd);

	}
	return 0;
}
