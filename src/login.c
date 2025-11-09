#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char usernameFile[20], passwordFile[20], roleFile[20];
    char username[20], password[20];
    int loginBerhasil = 0;

    // Cek input dari command line
    if (argc < 3) {
        printf("Cara pakai: %s <username> <password>\n", argv[0]);
        return 1;
    }

    // Ambil username dan password
    strcpy(username, argv[1]);
    strcpy(password, argv[2]);

    // Buka file akun.txt
    file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("File akun.txt tidak ditemukan!\n");
        return 1;
        }

    // Baca file baris per baris
    while (fscanf(file, "%s %s %s", usernameFile, passwordFile, roleFile) != EOF) {
        // Cek apakah cocok
        if (strcmp(username, usernameFile) == 0 && strcmp(password, passwordFile) == 0) {
            printf("Login berhasil! Anda adalah %s\n", roleFile);
            loginBerhasil = 1;
            break;
        }
    }

    // Tutup file
    fclose(file);

    // Jika tidak berhasil
    if (loginBerhasil == 0) {
        printf("Login gagal! Username atau password salah.\n");
    }

    return 0;
}
