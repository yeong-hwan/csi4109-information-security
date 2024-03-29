#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 256
#define MAX_FILENAME_LENGTH 256
#define MAX_POLICY_LENGTH 256

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    int permission;
} UserPermission;

UserPermission *get_user_permission(int uid)
{
    // get mac.policy
    FILE *policy_file = fopen("mac.policy", "r");
    if (policy_file == NULL)
    {
        // perror("Error opening mac.policy");
        exit(1);
    }

    UserPermission *permissions = malloc(MAX_POLICY_LENGTH * sizeof(UserPermission));
    int num_permissions = 0;

    char line[MAX_POLICY_LENGTH];
    while (fgets(line, sizeof(line), policy_file) != NULL)
    {
        char *username = strtok(line, ":");
        char *permission_str = strtok(NULL, "\n");
        

        // printf("%s\n", username);
        // printf("%s\n", permission_str);

        int permission = -1;

        if (strcmp(permission_str, "UNCLASSIFIED") == 0)
        {
            permission = 0;
        }
        else if (strcmp(permission_str, "CONFIDENTIAL") == 0)
        {
            permission = 1;
        }
        else if (strcmp(permission_str, "SECRET") == 0)
        {
            permission = 2;
        }
        else if (strcmp(permission_str, "TOP_SECRET") == 0)
        {
            permission = 3;
        }

        // printf("permission : %d\n\n", permission);

        if (permission != -1)
        {
            UserPermission user_permission;
            strncpy(user_permission.username, username, MAX_USERNAME_LENGTH);
            user_permission.permission = permission;
            permissions[num_permissions++] = user_permission;
        }
    }

    fclose(policy_file);

    return permissions;
}

int main(int argc, char *argv[])
{

    char *subcommand = argv[1];
    char *filename = argv[2];
    char *file_content;


    if (strcmp(argv[1], "read") != 0)
    {
        file_content = argv[3];
    }

    bool write_flag = false;


    int uid = getuid();
    UserPermission *user_permissions = get_user_permission(uid);

    int num_user_permissions = sizeof(*user_permissions);
    int user_permission = -1;

    // printf("%lu\n", sizeof(UserPermission));
    // printf("%d\n", num_user_permissions);

    char  *current_username;
    struct passwd *user_pw;

    user_pw = getpwuid(uid); // get user info using uid
    current_username = user_pw->pw_name;

    for (int i = 0; i < num_user_permissions; i++)
    {
        // get login = root 
        // printf("%d | user_permission : %s\n", i, user_permissions[i].username);

        if (strcmp(user_permissions[i].username, current_username) == 0)
        {
            user_permission = user_permissions[i].permission;
            // printf("%d\n", user_permission); 
            break;
        }
    }

    if (user_permission == -1)
    {
        printf("ACCESS DENIED\n");
        exit(0);
    }

    char contents[1024];
    if (strcmp(filename, "unclassified.data") == 0)
    {
        if (strcmp(subcommand, "read") == 0) {
            FILE *file = fopen(filename, "r");
            if (file == NULL)
            {
                // perror("Error opening unclassified.data");
                exit(1);
            }
            fgets(contents, sizeof(contents), file);
            fclose(file);
        }
        else if (strcmp(subcommand, "write") == 0)
        {
            if (user_permission > 0) {
                strcpy(contents, "ACCESS DENIED");
            }
            else
            {
                write_flag = true;
            }
        }
    }
    else if (strcmp(filename, "confidential.data") == 0)
    {
        if (strcmp(subcommand, "read") == 0)
        {
            if (user_permission >= 1)
                {
                    FILE *file = fopen(filename, "r");
                    if (file == NULL)
                    {
                        // perror("Error opening confidential.data");
                        exit(1);
                    }
                    fgets(contents, sizeof(contents), file);
                    fclose(file);
                }
                else
                {
                    strcpy(contents, "ACCESS DENIED");
                }
        }
        else if (strcmp(subcommand, "write") == 0)
        {
            if (user_permission > 1) {
                strcpy(contents, "ACCESS DENIED");
            }
            else
            {
                write_flag = true;
            }
        }
        
    }
    else if (strcmp(filename, "secret.data") == 0)
    {
        if (strcmp(subcommand, "read") == 0)
        {
            if (user_permission >= 2)
            {
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    // perror("Error opening secret.data");
                    exit(1);
                }
                fgets(contents, sizeof(contents), file);
                fclose(file);
            }
            else
            {
                strcpy(contents, "ACCESS DENIED");
            }
        }
        else if (strcmp(subcommand, "write") == 0)
        {
            if (user_permission > 2) {
                strcpy(contents, "ACCESS DENIED");
            }
            else
            {
                write_flag = true;
            }
        }
    }
    else if (strcmp(filename, "top_secret.data") == 0)
    {
        if (strcmp(subcommand, "read") == 0)
        {
            if (user_permission >= 3)
            {
                FILE *file = fopen(filename, "r");
                if (file == NULL)
                {
                    // perror("Error opening top_secret.data");
                    exit(1);
                }
                char* content = fgets(contents, sizeof(contents), file);
                printf("%s\n", content);
                fclose(file);
            }
            else
            {
                strcpy(contents, "ACCESS DENIED");
            }
        }
        else if (strcmp(subcommand, "write") == 0)
        {
            if (user_permission > 3) {
                strcpy(contents, "ACCESS DENIED");
            }
            else
            {
                write_flag = true;
            }
        }
    }
    else
    {
        strcpy(contents, "ACCESS DENIED");
    }

    // drop root permission
    seteuid(getuid());
    setegid(getgid());

    // logging and printing
    int log_file = open(strcat(current_username, ".log"), O_WRONLY | O_APPEND | O_CREAT, 0640);
    if (log_file == -1)
    {
        // Error opening log file
        exit(1);
    }

    dprintf(log_file, "%s %s\n", subcommand, filename);
    close(log_file);

    if (!write_flag)
    {
        printf("%s\n", contents);
    }

    free(user_permissions);

    return 0;
}
