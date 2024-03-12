#include "./utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define MAX_OWNER_NAME_LENGTH 100000

typedef struct House
{
    struct House *this;

    char *owner_name;
    char **keys;

    // insides
    struct Node *head;

} House;

typedef struct State
{
    // char *user_name;
    char *key;
    bool allowed;
} State;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("%s\n", "CHECK YOUR USAGE: ./secure_house <owner_name> <key_1> <key_2> ... <key_n>");
        return 0;
    }

    // House initial constructor
    House house;
    State state;
    house.owner_name = argv[1];

    int key_count = argc - 2;
    house.keys = malloc(sizeof(char *) * key_count + 1);
    house.keys[key_count] = 0;

    for (int i = 0; i < key_count; i++)
    {
        house.keys[i] = argv[i + 2];
    }

    house.head = NULL;

    char *line = NULL;          // Pointer to hold the line
    size_t bufsize = 0;         // Size of the buffer
    ssize_t linelen;            // Length of the line read
    char *token;                // Pointer to hold each token
    char delimiter[] = " \t\n"; // Delimiters (space, tab, newline)

    char *user_name;

    int idx = 0;

    // Read lines until EOF
    while ((linelen = getline(&line, &bufsize, stdin)) != -1)
    {
        idx++;

        // If the line ends with '\n', remove it
        if (line[linelen - 1] == '\n')
            line[linelen - 1] = '\0';

        // Print the line
        printf("\n%d. ", idx);
        printf("%s\n", line);

        // Tokenize the line by space, tab, or newline
        token = strtok(line, delimiter);
        // printf("%s\n", token);

        // End program at EOF
        if (token == NULL)
        {
            break;
        }

        if (strcmp(token, "INSERT") == 0)
        { // pass "KEY" token
            state.key = NULL;
            state.allowed = false;

            token = strtok(NULL, delimiter);
            user_name = strtok(NULL, delimiter);
            state.key = strtok(NULL, delimiter);

            printf("KEY %s INSERTED BY %s\n", state.key, user_name);
        }
        else if (strcmp(token, "TURN") == 0)
        { // pass "KEY" token
            token = strtok(NULL, delimiter);
            user_name = strtok(NULL, delimiter);
            bool key_success = false;

            if (state.key == NULL)
            {
                printf("FAILURE %s HAD NO KEY INSERTED\n", user_name);
                break;
            }

            for (int i = 0; i < key_count; i++)
            {

                else if (strcmp(state.key, house.keys[i]) == 0)
                {
                    printf("SUCCESS %s TURNS KEY %s\n", user_name, state.key);
                    key_success = true;
                    state.allowed = true;
                    break;
                }
            }

            if (!key_success)
            {
                printf("FAILURE %s HAD INVALID KEY %s INSERTED\n", user_name, state.key);
                state.allowed = false;
            }
        }
        else if (strcmp(token, "ENTER") == 0)
        { // pass "HOUSE" token
            token = strtok(NULL, delimiter);

            user_name = strtok(NULL, delimiter);

            if (state.allowed)
            {
                printf("%s", "ACCESS ALLOWED");
                // user_name 추가 필요
            }
            else
            {
                printf("%s", "ACCESS DENIED");
            }
        }
        else if (strcmp(token, "WHO'S") == 0)
        { // pass "INSIDE?" token
            token = strtok(NULL, delimiter);
        }
        else if (strcmp(token, "CHANGE") == 0)
        { // pass "LOCKS" token
            token = strtok(NULL, delimiter);

            user_name = strtok(NULL, delimiter);

            while (token != NULL)
            {
                // Print each token
                printf("%s\n", token);
                // Get the next token
                token = strtok(NULL, delimiter);
            }
        }
        else if (strcmp(token, "LEAVE") == 0)
        { // pass "HOUSE" token
            token = strtok(NULL, delimiter);

            user_name = strtok(NULL, delimiter);
        }

        // printf("user_name: %s\n", user_name);
    }

    // Free the memory allocated for the line
    free(line);

    return 0;
}