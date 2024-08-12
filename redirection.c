#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "redirection.h"

#define MAX_ARGS 150

void runCommand(char **parsed, streamFiles *mystream, int append) {
    pid_t pid = fork();
    if (pid == 0) {

        if (mystream->inputFile != NULL && strcmp(mystream->inputFile, "") != 0) {
            int fd = open(mystream->inputFile, O_RDONLY);
            if (fd == -1) {
                perror("Failed to open input file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (mystream->outputFile != NULL && strcmp(mystream->outputFile, "") != 0) {
            int fd;
            if (append) {
                fd = open(mystream->outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(mystream->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd == -1) {
                perror("Failed to open output file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (mystream->errorFile != NULL && strcmp(mystream->errorFile, "") != 0) {
            int fd = open(mystream->errorFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Failed to open error file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDERR_FILENO);
            close(fd);
        }
	terminateCommand(argcnt, parsedCmd, parsedPipe, processFlag);
       // execvp(parsed[0], parsed);
       // perror("Execution failed");
       // exit(EXIT_FAILURE);
       exit(0);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}
