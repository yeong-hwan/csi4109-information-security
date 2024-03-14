#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the linked list
struct Node
{
    char *data;
    struct Node *next;
};

// Function to create a new node with given data
struct Node *createNode(const char *data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the linked list
// void insertAtBeginning(struct Node **head, const char *data)
// {
//     struct Node *newNode = createNode(data);
//     newNode->next = *head;
//     *head = newNode;
// }

// Function to insert a new node at the end of the linked list
void insertAtLast(struct Node **head, const char *data)
{
    struct Node *newNode = createNode(data);

    if (*head == NULL)
    {
        // If the list is empty, make the new node the head node
        *head = newNode;
    }
    else
    {
        // Traverse the list to find the last node
        struct Node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        // Insert the new node after the last node
        current->next = newNode;
    }
}

// Function to print the linked list
void printList(struct Node *head)
{
    struct Node *temp = head;
    if (temp->next != NULL)
    {
        temp = temp->next;
    }

    while (temp->next != NULL)
    {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("%s", temp->data);
    printf("\n");
}

// Function to check if a node with a specific data value exists in the linked list
int checkNode(struct Node *head, const char *data)
{
    struct Node *current = head;

    // Traverse the list and search for the node with the specified data value
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
        {
            return 1; // Node with the specified data value found
        }
        current = current->next;
    }

    return 0; // Node with the specified data value not found
}

// Function to delete all nodes with a specific data value from the linked list
void deleteNodes(struct Node **head, const char *data)
{
    struct Node *current = *head;
    struct Node *prev = NULL;

    // Traverse the list and delete all nodes with the specified data value
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            struct Node *temp = current;
            current = current->next;
            free(temp->data); // Free the memory allocated for the string
            free(temp);       // Free the memory allocated for the node
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

int lengthOfList(struct Node *head)
{
    int length = 0;
    struct Node *current = head;

    // Traverse the list and count the number of nodes
    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}

// Function to free the memory allocated for the linked list
// void freeList(struct Node *head)
// {
//     struct Node *temp;
//     while (head != NULL)
//     {
//         temp = head;
//         head = head->next;
//         free(temp->data); // Free the memory allocated for the string
//         free(temp);
//     }
// }