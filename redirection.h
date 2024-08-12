#ifndef RED_H_
#define RED_H_ 

#define MAXARG 150

typedef struct
{
	char inputFile[256];
	char outputFile[256];
	char errorFile[256];

}streamFiles;

extern char cmd[1024], *parsedCmd[MAXARG], *parsedPipe[MAXARG], cmd2[1024], cmd3[1024];
extern int processFlag, redirectionFlag, argcnt;

void runCommand(char **parsed, streamFiles *mystream, int append);
//void runCommand(char ** parsed, char *inputFile, char *outputFile, char *errorFile, int append);

#endif
