#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        printf("$ ");
        nread = getline(&line, &len, stdin);
        if (nread == -1) {
            if (feof(stdin)) {
                exit(EXIT_SUCCESS);
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        if (line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        char *token = strtok(line, " ");
        char *argv[100];
        int argc = 0;
        while (token != NULL) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(argv[0], argv) == -1) {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            wait(&status);
        }
    }
}

