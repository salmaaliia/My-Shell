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
#include "piping.h"
#include "myfree.h"
#include "myuptime.h"
#include "redirection.h"

#define MAXARG 150
char *inputFile = NULL;
char *outputFile = NULL;
char *errorFile = NULL;

void  terminateCommand(int sz, char **parsedCmd, char **parsedPipe, int pipeFlag)
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
        else if(strcmp(parsedCmd[0], "myfree") == 0)
        {
                printMemoryInfo();
        }
        else if(strcmp(parsedCmd[0], "myuptime") == 0)
        {
                printUptime();
        }
	else {
		if(pipeFlag == 2)
		{
		       	executePiped(parsedCmd, parsedPipe);
		}
		else if(pipeFlag == 0){
		      	runExternal(parsedCmd);
		}
        }
}
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

int parsePipeCommand(char *cmd, char **cmdPiped)
{
	int i; 
	for (i = 0; i < 2; i++)
	{
		cmdPiped[i] = strsep(&cmd, "|");
		if(cmdPiped[i] == NULL)
			break;
	}

	if (cmdPiped[1] == NULL)
		return 0;
       	else {
	       	return 1;
    	}
}
int  parseCommand(char *cmd, char ** parsed)
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

int redirectionCmd(char *cmd)
{
	int i = 0, red = 0;
	char *token;
//	*append = 0;
	while((token = strsep(&cmd, " ")) != NULL)
	{
		if (strcmp(token, "<") == 0
			|| strcmp(token, ">") == 0
			||strcmp(token, ">>") == 0
			||strcmp(token, "2>") == 0)
		{
			red = 1;
		}
	}

	return red;

}
int processCommand(char *cmd, char ** parsed, char **parsedPipe, int* argcnt)
{
	char* cmdPiped[2], cmd2[MAXARG], cmd3[MAXARG];
	int piped = 0, redirection = 0;
	strcpy(cmd2, cmd);
	strcpy(cmd3, cmd);

	redirection = redirectionCmd(cmd2);
        if(redirection)
                return 1;
	piped = parsePipeCommand(cmd, cmdPiped);

	if(piped)
	{
		 parseCommand(cmdPiped[0], parsed);
		 parseCommand(cmdPiped[1], parsedPipe);
	}
	else
	{
		*argcnt = parseCommand(cmd, parsed);
	}

	 if(piped)
		return 2;
	else 
		return 0;

//	return piped;
}

int main()
{
	char cmd[1024], *parsedCmd[MAXARG], *parsedPipe[MAXARG];
	int processFlag = 0, argcnt;
	
	while(1)
	{
		processFlag = 0;
		currentDir();

		if(takeCommand(cmd) == 1) continue;

	//	int sz = parseCommand(cmd, parsedCmd);
	//	terminateCommand(sz, parsedCmd);

		processFlag = processCommand(cmd, parsedCmd, parsedPipe,  &argcnt);
		if(processFlag == 1)
			runCommand(cmd);
		else{
			terminateCommand(argcnt, parsedCmd, parsedPipe, processFlag);
		}

	}
	return 0;
}
