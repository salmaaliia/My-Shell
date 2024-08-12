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
#include "terminate.h"

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
                if(pipeFlag)
                {
                        executePiped(parsedCmd, parsedPipe);
                }
                else{
                        runExternal(parsedCmd);
                }
        }

}
     
