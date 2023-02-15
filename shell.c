#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            char *argv[] = {line, NULL};
            if (execve(argv[0], argv, NULL) == -1) {
                perror(line);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            wait(&status);
        }
    }
}

