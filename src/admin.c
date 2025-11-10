<<<<<<< HEAD
=======
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    unsigned int id;
    char nama[50];
    char merek[50];
    char model[50];
    unsigned int tahun;
    unsigned int jumlah;
} Alatlab;

void tampilkan_alat(){
    FILE *file = fopen("alat.txt", "r");
    if (!file) {
        printf("Belum ada data alat.txt\n");
        return;
    }

    Alatlab alat;
    printf("\n================= Daftar Alat Lab =================\n");
    while (fscanf(file, "%u,%s,%s,%s,%u,%u\n", 
                &alat.id, alat.nama, alat.merek, alat.model, 
                &alat.tahun, &alat.jumlah) != EOF) {
        printf("ID: %u\n", alat.id);
        printf("Nama: %s\n", alat.nama);
        printf("Merek: %s\n", alat.merek);
        printf("Model: %s\n", alat.model);
        printf("Tahun: %u\n", alat.tahun);
        printf("Jumlah: %u\n", alat.jumlah);
        printf("----------------------------------------\n");
    }
    fclose(file);
}

void tambah_alat(){
    FILE *file = fopen("alat.txt", "a");

    Alatlab alat;
    printf("Masukkan ID Alat: ");
    scanf("%u", &alat.id);
    printf("Masukkan Nama Alat: ");
    scanf(" %s", alat.nama);
    printf("Masukkan Merek Alat: ");
    scanf(" %s", alat.merek);
    printf("Masukkan Model Alat: ");
    scanf(" %s", alat.model);
    printf("Masukkan Tahun Produksi Alat: ");
    scanf("%u", &alat.tahun);
    printf("Masukkan Jumlah Unit Alat: ");
    scanf("%u", &alat.jumlah);

    fprintf(file, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    fclose(file);
    printf("Data alat berhasil ditambahkan.\n");
}

void edit_alat(){
    FILE *file = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file) {
        printf("Belum ada data alat.txt\n");
        return;
    }

    unsigned int id;
    Alatlab alat;
    int found = 0;

    printf("Masukkan ID Alat yang akan diedit: ");
    scanf("%u", &id);
    while (fscanf(file, "%u,%s,%s,%s,%u,%u\n", 
                &alat.id, alat.nama, alat.merek, alat.model, 
                &alat.tahun, &alat.jumlah) != EOF) {
        if (alat.id == id) {
            found = 1;
            printf("Data ditemukan. Masukkan data baru.\n");
            printf("Masukkan Nama Alat: ");
            scanf(" %s", alat.nama);
            printf("Masukkan Merek Alat: ");
            scanf(" %s", alat.merek);
            printf("Masukkan Model Alat: ");
            scanf(" %s", alat.model);
            printf("Masukkan Tahun Produksi Alat: ");
            scanf("%u", &alat.tahun);
            printf("Masukkan Jumlah Unit Alat: ");
            scanf("%u", &alat.jumlah);
    }
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove("alat.txt");
        rename("temp.txt", "alat.txt");
        printf("Data alat berhasil diupdate.\n");
    } else {
        remove("temp.txt");
        printf("Data dengan ID %u tidak ditemukan.\n", id);
    }
}

void hapus_alat(){
    FILE *file = fopen("alat.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!file) {
        printf("Belum ada data alat.txt\n");
        return;
    }

    unsigned int id;
    Alatlab alat;
    int found = 0;

    printf("Masukkan ID Alat yang akan dihapus: ");
    scanf("%u", &id);
    while (fscanf(file, "%u,%s,%s,%s,%u,%u\n", 
                &alat.id, alat.nama, alat.merek, alat.model, 
                &alat.tahun, &alat.jumlah) != EOF) {
        if (alat.id == id) {
            found = 1;
            continue;
        }
        fprintf(temp, "%u,%s,%s,%s,%u,%u\n", alat.id, alat.nama, alat.merek, alat.model, alat.tahun, alat.jumlah);
    }
    fclose(file);
    fclose(temp);

    if (found) {
        remove("alat.txt");
        rename("temp.txt", "alat.txt");
        printf("Data alat berhasil dihapus.\n");
    } else {
        remove("temp.txt");
        printf("Data dengan ID %u tidak ditemukan.\n", id);
    }
}

int login_admin(){
    char username[50];
    char password[50];

    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        return 1;
    } else {
        printf("Username atau password salah.\n");
        return 0;
    }
}

void menu_admin(){
    int pilihan;
    if (!login_admin()) {
        return;
    }

    do {
        printf("\n===== Menu Admin =====\n");
        printf("1. Tampilkan Alat\n");
        printf("2. Tambah Alat\n");
        printf("3. Edit Alat\n");
        printf("4. Hapus Alat\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkan_alat();
                break;
            case 2:
                tambah_alat();
                break;
            case 3:
                edit_alat();
                break;
            case 4:
                hapus_alat();
                break;
            case 5:
                printf("Keluar dari menu admin.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 5);
}

int main(){
    printf("===== LOGIN ADMIN =====\n");
    if (login_admin()) {
        menu_admin();
    } else {
        printf("Login gagal.\n");
    }
    return 0;
}
>>>>>>> 879d0bc4f630368b39e05cb0da6b23707c27e46c
