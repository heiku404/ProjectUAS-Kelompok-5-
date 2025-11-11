#include "../include/utils.h"

int login(char *username, char *password)
{
    char temp_username[MAX_ALAT]; 
    char temp_password[MAX_ALAT];

    FILE *fptr;
    fptr = fopen(ADMIN_PATH, "r"); 

    if (fptr == NULL)
    {
        printf("Error : file %s tidak ditemukan\n", ADMIN_PATH);
        return 0;
    }

    while (fscanf(fptr, "%s %s", temp_username, temp_password) == 2)
    {
        if (strcmp(username, temp_username) == 0 && strcmp(password, temp_password) == 0)
        {
            fclose(fptr);
            return 1; // 1 untuk Admin
        }
    }

    fclose(fptr);

    fptr = fopen(USER_PATH, "r"); // Menggunakan USER_PATH dari utils.h

    if (fptr == NULL)
    {
        printf("Error : file %s tidak ditemukan\n", USER_PATH);
        return 0;   
    }

    while (fscanf(fptr, "%s %s", temp_username, temp_password) == 2)
    {
        if (strcmp(username, temp_username) == 0 && strcmp(password, temp_password) == 0)
        {
            fclose(fptr);
            return 2; // 2 untuk User
        }
    }
    fclose(fptr);

    printf("Login failed. Username atau password salah.\n");
    return 0; // 0 untuk Gagal
}