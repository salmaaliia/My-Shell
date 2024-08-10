#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "piping.h"
#include <sys/wait.h>
void executePiped(char** parsed, char** parsedpipe)
{
    int pipefd[2];
    pid_t p1, p2;

    if (pipe(pipefd) < 0) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    p1 = fork();
    if (p1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (p1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        if (execvp(parsed[0], parsed) < 0) {
            perror("Execvp failed for command 1");
            exit(EXIT_FAILURE);
        }
    } else {
        p2 = fork();
        if (p2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (p2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);

            if (execvp(parsedpipe[0], parsedpipe) < 0) {
                perror("Execvp failed for command 2");
                exit(EXIT_FAILURE);
            }
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(p1, NULL, 0);
	    waitpid(p2, NULL, 0);
        }
    }
}
