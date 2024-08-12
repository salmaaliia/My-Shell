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
#include "terminate.h"
#define MAXARG 150


char cmd[1024], *parsedCmd[MAXARG], *parsedPipe[MAXARG], cmd2[1024], cmd3[1024];
int processFlag = 0, redirectionFlag = 0, argcnt;

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

int redirectionCmd(char *cmd, char *cmd2, streamFiles *mystream)
{
	int i = 0, red = 0;
	char *token, mycmd[1024] = "", *str;
	int append = 0;
	while((token = strsep(&cmd, " ")) != NULL)
	{
		if(strcmp(token, "<") == 0)
		{
			str = strsep(&cmd, " ");
			if (str != NULL) {
				strcpy(mystream->inputFile, str);
			}
			red = 1;
		}	
		else if(strcmp(token, ">") == 0)
                {      
		       	str = strsep(&cmd, " ");
                        if (str != NULL) {
				strcpy(mystream->outputFile, str);
			}
                        red = 1;
                } 
                else if(strcmp(token, ">>") == 0)
                {
			str = strsep(&cmd, " ");
                        if (str != NULL) {
		       		strcpy(mystream->outputFile, str);
			}
			append = 1;
                        red = 1;
                }
                else if(strcmp(token, "2>") == 0)
                {
			str = strsep(&cmd, " ");
        		if (str != NULL) {
				strcpy(mystream->errorFile, str);
			}
			red = 1;
                }
		else if(*token != '\0')
		{ 
			strcat(mycmd, token);
			strcat(mycmd, " ");
		}
	}
	strcpy(cmd2, mycmd);

	return red + append;

}
int processCommand(char *cmd, char ** parsed, char **parsedPipe, int* argcnt)
{
	char* cmdPiped[2], cmd2[1024], cmd3[1024];
	int piped = 0, redirection = 0;

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


	return piped;
}

int main()
{
	
	streamFiles mystream;
	strcpy(mystream.inputFile, "");
	strcpy(mystream.outputFile, "");
	strcpy(mystream.errorFile, "");
	while(1)
	{
		processFlag = 0;
		currentDir();

		if(takeCommand(cmd) == 1) continue;

		redirectionFlag = redirectionCmd(cmd, cmd2, &mystream);
		processFlag = processCommand(cmd2, parsedCmd, parsedPipe,  &argcnt);
		if(redirectionFlag)
		{
			runCommand(parsedCmd, &mystream, redirectionFlag - 1);
		}
		else{
			terminateCommand(argcnt, parsedCmd, parsedPipe, processFlag);
		}

	}
	return 0;
}
