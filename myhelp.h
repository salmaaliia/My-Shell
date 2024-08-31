#ifndef MYHELP_H_
#define MYHELP_H_

typedef enum {
    CMD_MYCP,
    CMD_MYMV,
    CMD_MYPWD,
    CMD_MYECHO,
    CMD_MYHELP,
    CMD_MYEXIT,
    CMD_MYTYPE,
    CMD_ENVI,
    CMD_MYCD, 
    CMD_MYUPTIME,
    CMD_MYFREE,
    CMD_UNKNOWN
} CommandType;

CommandType getCommandType(const char *cmd);

void printHelp(CommandType cmdType);

void runMyhelp(int argcnt, char **args);
#endif

