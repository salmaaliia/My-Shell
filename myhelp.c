#include <stdio.h>
#include <string.h>
#include "myhelp.h"


CommandType getCommandType(const char *cmd) {
    if (strcmp(cmd, "mycp") == 0) return CMD_MYCP;
    if (strcmp(cmd, "mymv") == 0) return CMD_MYMV;
    if (strcmp(cmd, "mypwd") == 0) return CMD_MYPWD;
    if (strcmp(cmd, "myecho") == 0) return CMD_MYECHO;
    if (strcmp(cmd, "myhelp") == 0) return CMD_MYHELP;
    if (strcmp(cmd, "myexit") == 0) return CMD_MYEXIT;
    if (strcmp(cmd, "mytype") == 0) return CMD_MYTYPE;
    if (strcmp(cmd, "envir") == 0) return CMD_ENVI;
    if (strcmp(cmd, "mycd") == 0) return CMD_MYCD;
    return CMD_UNKNOWN;
}

void printHelp(CommandType cmdType){
    switch (cmdType) {
        case CMD_MYCP:
            printf("mycp <source> <destination>\n");
            printf("  Copies the file from <source> to <destination>.\n");
            break;
        case CMD_MYMV:
            printf("mymv <source> <destination>\n");
            printf("  Moves the file from <source> to <destination>.\n");
            break;
        case CMD_MYPWD:
            printf("mypwd\n");
            printf("  Prints the current working directory.\n");
            break;
        case CMD_MYECHO:
            printf("myecho <message>\n");
            printf("  Prints <message> to the standard output.\n");
            break;
        case CMD_MYHELP:
            printf("myhelp\n");
            printf("  Displays this help message.\n");
            break;
        case CMD_MYEXIT:
            printf("myexit\n");
            printf("  Exits the program.\n");
            break;
        case CMD_MYTYPE:
            printf("mytype <command>\n");
            printf("  Displays information about the command (built-in or external).\n");
            break;
        case CMD_ENVI:
            printf("envir [<variable>]\n");
            printf("  Displays the environment variables. If <variable> is provided, prints its value.\n");
            break;
        case CMD_MYCD:
            printf("mycd <directory>\n");
            printf("  Changes the current directory to <directory>.\n");
            break;
        case CMD_UNKNOWN:
        default:
            printf("Unknown command.\n");
            break;
    }
 }	    
void runMyhelp(int argcnt, char **args)
{
	if(argcnt == 1)
	{
		printf("Available commands:\n");
    		printf("\n");
    		printf("mycp <source> <destination>\n");
   		printf("  Copies the file from <source> to <destination>.\n");
    		printf("\n");
    		printf("mymv <source> <destination>\n");
   		printf("  Moves the file from <source> to <destination>.\n");
    		printf("\n");
   		printf("mypwd\n");
   	 	printf("  Prints the current working directory.\n");
    		printf("\n");
    		printf("myecho <message>\n");
    		printf("  Prints <message> to the standard output.\n");
    		printf("\n");
    		printf("myhelp\n");
		printf("  Displays this help message.\n");
	       	printf("\n");
   		printf("myexit\n");
   		printf("  Exits the program.\n");
		printf("\n");
		printf("mytype <command>\n");
		printf("  Displays information about the command (built-in or external).\n");
		printf("\n");
		printf("envir [<variable>]\n");
	      	printf("  Displays the environment variables. If <variable> is provided, prints its value.\n");
		printf("\n");
		printf("mycd <directory>\n");
		printf("  Changes the current directory to <directory>.\n");
    	//	printf("\n");
	}
	else
	{
		for(int i = 1; i < argcnt; i++)
	 	{
	 		printHelp(getCommandType(args[i]));		
	       	}

	}
}
