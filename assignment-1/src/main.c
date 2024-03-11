#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[])
{
    // printf("%d\n", argc);
    // printf("%s\n", argv[1]);

    if (argc < 3)
    {
        printf("%s\n", "CHECK YOUR USAGE: ./secure_house <owner_name> <key_1> <key_2> ... <key_n>");
        return 0;
    }

    char *line = NULL;  // Pointer to hold the line
    size_t bufsize = 0; // Size of the buffer
    ssize_t linelen;    // Length of the line read

    // Read lines until EOF
    while ((linelen = getline(&line, &bufsize, stdin)) != -1)
    {
        // If the line ends with '\n', remove it
        if (line[linelen - 1] == '\n')
            line[linelen - 1] = '\0';

        // Print the line
        printf("%s\n", line);
    }

    return 0;
}