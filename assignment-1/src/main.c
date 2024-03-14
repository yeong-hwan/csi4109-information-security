#include "./utils.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    // Linked List Test ----------------------------
    house.head->data = "HEAD";
    house.head->next = NULL;
    // printList(house.head);

    // insertAtLast(&house.head, "test2");
    // insertAtLast(&house.head, "test3");
    // insertAtLast(&house.head, "test4");

    // printList(house.head);

    // printf("%d\n", checkNode(house.head, "test2"));
    // printf("%d\n", checkNode(house.head, "test5"));

    // deleteNodes(&house.head, "test2");

    // printList(house.head);

    // printf("%d\n", lengthOfList(house.head));

    // printf("%s", house.head->data);

    // Linked List Test ----------------------------

    int key_count = argc - 2;
    house.keys = malloc(sizeof(char *) * key_count + 1);
    house.keys[key_count] = 0;

    for (int i = 0; i < key_count; i++)
    {
        house.keys[i] = argv[i + 2];
    }

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
        // printf("\n%d. ", idx);
        // printf("%s\n", line);

        // Tokenize the line by space, tab, or newline
        token = strtok(line, delimiter);

        // End program at EOF
        if (token == NULL)
        {
            break;
        }

        if (strcmp(token, "INSERT") == 0)
        { // pass "KEY" token
            token = strtok(NULL, delimiter);

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            state.key = NULL;
            state.allowed = false;
            user_name = strtok(NULL, delimiter);
            state.key = strtok(NULL, delimiter);

            if (user_name == NULL || state.key == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            printf("KEY %s INSERTED BY %s\n", state.key, user_name);
        }
        else if (strcmp(token, "TURN") == 0)
        { // pass "KEY" token
            token = strtok(NULL, delimiter);

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            user_name = strtok(NULL, delimiter);
            bool key_success = false;

            if (user_name == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            if (state.key == NULL)
            {
                printf("FAILURE %s HAD NO KEY INSERTED\n", user_name);
                break;
            }

            for (int i = 0; i < key_count; i++)
            {
                if (strcmp(state.key, house.keys[i]) == 0)
                {
                    printf("SUCCESS %s TURNS KEY %s\n", user_name, state.key);
                    key_success = true;
                    state.allowed = true;
                    break;
                }
            }

            if (strcmp(state.key, "FIREFIGHTER_SECRET_KEY") == 0)
            {
                printf("SUCCESS %s TURNS KEY %s\n", user_name, state.key);
                key_success = true;
                state.allowed = true;
                break;
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

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            user_name = strtok(NULL, delimiter);

            if (user_name == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            if (state.allowed)
            {
                printf("%s\n", "ACCESS ALLOWED");

                insertAtLast(&house.head, user_name);
            }
            else
            {
                printf("%s\n", "ACCESS DENIED");
            }
        }
        else if (strcmp(token, "WHO'S") == 0)
        { // pass "INSIDE?" token
            token = strtok(NULL, delimiter);

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            int list_length = lengthOfList(house.head);
            if (list_length == 1)
            {
                printf("%s", "NOBODY HOME");
            }
            else
            {
                printList(house.head);
            }
        }
        else if (strcmp(token, "CHANGE") == 0)
        { // pass "LOCKS" token
            token = strtok(NULL, delimiter);

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            user_name = strtok(NULL, delimiter);

            if (user_name == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

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

            if (token == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            user_name = strtok(NULL, delimiter);

            if (user_name == NULL)
            {
                printf("%s", "ERROR");
                break;
            }

            int is_in_house = checkNode(house.head, user_name);

            if (is_in_house)
            {
                printf("%s LEFT", user_name);
                deleteNodes(&house.head, user_name);
            }
            else
            {
                printf("%s NOT HERE", user_name);
            }
        }
        else
        {
            printf("%s", "ERROR");
        }

        // printf("user_name: %s\n", user_name);
    }

    // Free the memory allocated for the line
    free(line);

    return 0;
}