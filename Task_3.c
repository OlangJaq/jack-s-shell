#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * main - Simple shell
 *
 * Return: 0
 */
int main(void)
{
    char *buffer = NULL, *path = NULL, *token = NULL, *full_path = NULL;
    size_t bufsize = 0;
    ssize_t characters = 0;
    pid_t pid;
    int status;

    while (1)
    {
        printf("$ ");
        characters = getline(&buffer, &bufsize, stdin);
        if (characters == -1)
        {
            putchar('\n');
            break;
        }

        buffer[characters - 1] = '\0'; /* remove the newline character */

        /* check if command exists in PATH */
        path = getenv("PATH");
        token = strtok(path, ":");
        while (token != NULL)
        {
            full_path = malloc(strlen(token) + strlen(buffer) + 2);
            sprintf(full_path, "%s/%s", token, buffer);
            if (access(full_path, F_OK) == 0)
            {
                pid = fork();
                if (pid == -1)
                {
                    perror("Error");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    execve(full_path, NULL, environ);
                    perror(buffer);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    wait(&status);
                    break;
                }
            }
            free(full_path);
            token = strtok(NULL, ":");
        }
        if (token == NULL)
            printf("%s: command not found\n", buffer);
    }

    free(buffer);
    return (0);
}

