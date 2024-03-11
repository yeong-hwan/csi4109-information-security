#include "./utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_OWNER_NAME_LENGTH 100000

typedef struct House
{
    struct House *this;

    char *owner_name;
    char **keys;
    struct Node *head;

} House;

int main(int argc, char *argv[])
{
    // printf("%d\n", argc);
    // printf("%s\n", argv[1]);

    if (argc < 3)
    {
        printf("%s\n", "CHECK YOUR USAGE: ./secure_house <owner_name> <key_1> <key_2> ... <key_n>");
        return 0;
    }

    House house;
    house.owner_name = argv[1];

    int key_count = argc - 2;
    house.keys = malloc(sizeof(char *) * key_count + 1);
    house.keys[key_count] = 0;

    for (int i = 0; i < key_count; i++)
    {
        house.keys[i] = argv[i + 2];
    }

    house.head = NULL;

    // printf("%s\n", house.owner_name);

    // for (int i = 0; i < key_count; i++)
    // {
    //     printf("%s\n", house.keys[i]);
    // }

    char *line = NULL;          // Pointer to hold the line
    size_t bufsize = 0;         // Size of the buffer
    ssize_t linelen;            // Length of the line read
    char *token;                // Pointer to hold each token
    char delimiter[] = " \t\n"; // Delimiters (space, tab, newline)

    // Read lines until EOF
    while ((linelen = getline(&line, &bufsize, stdin)) != -1)
    {
        // If the line ends with '\n', remove it
        if (line[linelen - 1] == '\n')
            line[linelen - 1] = '\0';

        // Print the line
        printf("\n%s\n", line);

        // Tokenize the line by space, tab, or newline
        token = strtok(line, delimiter);
        while (token != NULL)
        {
            // Print each token
            printf("%s\n", token);
            // Get the next token
            token = strtok(NULL, delimiter);
        }
    }

    // Free the memory allocated for the line
    free(line);

    return 0;
}