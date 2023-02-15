#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

        if (strcmp(line, "exit\n") == 0)
        {
            exit(0);
        }

        printf("%s", line);
    }

    free(line);
    exit(EXIT_SUCCESS);
}

