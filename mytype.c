#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "mytype.h"

const char myShellPath[] = "/home/salma/Desktop/myShell";
const char *internalCMDs[] = {"mymv", "myecho", "myhelp", "myexit", "mytype", "envir", "mycp", "mycd", "mypwd", "myuptime", "myfree", NULL};

int internal(const char *cmd) {
    for (int i = 0; internalCMDs[i] != NULL; i++) {
        if (strcmp(cmd, internalCMDs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


void runMytype(char **args)
{
    if (args[1] == NULL) {
        printf("To use mytype: mytype <command>");
        return;
    }

    if (internal(args[1])) {
        printf("%s is a shell built-in command.", args[1]);
        return;
    }
    else
    {
        const char *path_env = getenv("PATH");
        if (path_env == NULL) {
            printf("PATH environment variable is not set.");
            return;
        }

        char path_copy[strlen(path_env) + 1];
        strcpy(path_copy, path_env);

        char *dir = path_copy;
        char *token;
        while ((token = strsep(&dir, ":")) != NULL) {
	    
//		if(strcmp(token, myShellPath))
//		    continue;

		char full_path[1024];
     		snprintf(full_path, sizeof(full_path), "%s/%s", token, args[1]);
    
		if(access(full_path, X_OK) == 0) {
                printf("%s is an external command located at %s.", args[1], full_path);
                return;
            }
        }

        printf("%s is not found.", args[1]);
    }


}


















