#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "redirection.h"

#define MAX_ARGS 150

void runCommand(char *cmd) {
    char *parsed[MAX_ARGS];
    char *inputFile = NULL;
    char *outputFile = NULL;
    char *errorFile = NULL;
    int append = 0;  

    int i = 0;
    char *token;
    while ((token = strsep(&cmd, " ")) != NULL) {
        if (strcmp(token, "<") == 0) {
            inputFile = strsep(&cmd, " ");
        } else if (strcmp(token, ">") == 0) {
            outputFile = strsep(&cmd, " ");
        } else if (strcmp(token, ">>") == 0) {
            outputFile = strsep(&cmd, " ");
            append = 1;
        } else if (strcmp(token, "2>") == 0) {
            errorFile = strsep(&cmd, " ");
        } else if (*token != '\0') { 
            parsed[i++] = token;
        }
    }
    parsed[i] = NULL;

    pid_t pid = fork();
    if (pid == 0) {

        if (inputFile) {
            int fd = open(inputFile, O_RDONLY);
            if (fd == -1) {
                perror("Failed to open input file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        if (outputFile) {
            int fd;
            if (append) {
                fd = open(outputFile, O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            if (fd == -1) {
                perror("Failed to open output file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (errorFile) {
            int fd = open(errorFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("Failed to open error file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        execvp(parsed[0], parsed);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}
