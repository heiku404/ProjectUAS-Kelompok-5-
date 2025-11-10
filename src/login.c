#include "../include/utils.h"

int login(char *username, char *password)
{
    char temp_username[maxSize];
    char temp_password[maxSize];

    FILE *fptr;
    fptr = fopen("../data/admin.txt", "r");

    if (fptr == NULL)
    {
        printf("Error : file admin.txt tidak ditemukan\n");
        return 0;
    }

    while (fscanf(fptr, "%s %s", temp_username, temp_password) == 2)
    {
        if (strcmp(username, temp_username) == 0 && strcmp(password, temp_password) == 0)
        {
            fclose(fptr);
            return 1;
        }
    }

    fclose(fptr);

    fptr = fopen("../data/user.txt", "r");

    if (fptr == NULL)
    {
        printf("Error : file admin.txt tidak ditemukan\n");
        return 0;   
    }

    while (fscanf(fptr, "%s %s", temp_username, temp_password) == 2)
    {
        if (strcmp(username, temp_username) == 0 && strcmp(password, temp_password) == 0)
        {
            fclose(fptr);
            return 2;
        }
    }
    fclose(fptr);

    printf("Login failed\n, username atau password yang dimasukkan salah\n");
    return 0;
}