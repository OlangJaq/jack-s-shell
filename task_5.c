#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1)
    {
        printf("$ ");
        read = getline(&line, &len, stdin);

        if (read == -1)
        {
            exit(0);
        }

        if (strcmp(line, "env\n") == 0)
        {
            for (int i = 0; environ[i] != NULL; i++)
            {
                printf("%s\n", environ[i]);
            }
        }

        printf("%s", line);
    }

    free(line);
    exit(EXIT_SUCCESS);
}

