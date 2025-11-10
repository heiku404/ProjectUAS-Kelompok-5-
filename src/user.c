#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALAT 100

struct Alat {
    unsigned int id;
    char nama[100];
    char merek[100];
    char model[100];
    unsigned int tahunProduksi;
    unsigned int jumlahUnit;
    unsigned int tersedia;
};

struct Alat daftarAlat[MAX_ALAT];
int jumlahAlat = 0;

// Simpan data ke file
void simpanKeFile() {
    FILE *file = fopen("alat.txt", "w");
    if (file == NULL) {
        printf("Gagal menyimpan ke file!\n");
        return;
    }
    for (int i = 0; i < jumlahAlat; i++) {
        fprintf(file, "%u;%s;%s;%s;%u;%u;%u\n",
                daftarAlat[i].id,
                daftarAlat[i].nama,
                daftarAlat[i].merek,
                daftarAlat[i].model,
                daftarAlat[i].tahunProduksi,
                daftarAlat[i].jumlahUnit,
                daftarAlat[i].tersedia);
    }
    fclose(file);
}

// Baca data dari file
void bacaDariFile() {
    FILE *file = fopen("alat.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file");
        fclose(file);
        return;
    }

    while (fscanf(file, "%u;%99[^;];%99[^;];%99[^;];%u;%u;%u\n",
                  &daftarAlat[jumlahAlat].id,
                  daftarAlat[jumlahAlat].nama,
                  daftarAlat[jumlahAlat].merek,
                  daftarAlat[jumlahAlat].model,
                  &daftarAlat[jumlahAlat].tahunProduksi,
                  &daftarAlat[jumlahAlat].jumlahUnit,
                  &daftarAlat[jumlahAlat].tersedia) == 7) {
        jumlahAlat++;
    }

    fclose(file);
}

/*  FUNGSI FITUR  */
// Lihat semua alat
void semuaAlat() {
    printf("\n=== DAFTAR SEMUA ALAT ===\n");
    printf("ID | Nama | Merek | Model | Tahun | Total | Tersedia\n");
    for (int i = 0; i < jumlahAlat; i++) {
        printf("%2u | %s | %s | %s | %u | %u | %u\n",
               daftarAlat[i].id,
               daftarAlat[i].nama,
               daftarAlat[i].merek,
               daftarAlat[i].model,
               daftarAlat[i].tahunProduksi,
               daftarAlat[i].jumlahUnit,
               daftarAlat[i].tersedia);
    }
}

// Lihat alat yang masih tersedia
void tersedia() {
    printf("\n=== ALAT YANG TERSEDIA ===\n");
    printf("ID | Nama | Merek | Model | Tahun | Total | Tersedia\n");

    int ada = 0;
    for (int i = 0; i < jumlahAlat; i++) {
        if (daftarAlat[i].tersedia > 0) {
            printf("%2u | %s | %s | %s | %u | %u | %u\n",
                   daftarAlat[i].id,
                   daftarAlat[i].nama,
                   daftarAlat[i].merek,
                   daftarAlat[i].model,
                   daftarAlat[i].tahunProduksi,
                   daftarAlat[i].jumlahUnit,
                   daftarAlat[i].tersedia);
            ada = 1;
        }
    }

    if (!ada) printf("Tidak ada alat yang tersedia.\n");
}

// Pinjam alat
void pinjamAlat() {
    unsigned int id;
    tersedia();
    printf("\nMasukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id);

    if (id < 1 || id > jumlahAlat) {
        printf("ID tidak valid!\n");
        return;
    }

    if (daftarAlat[id - 1].tersedia > 0) {
        daftarAlat[id - 1].tersedia--;
        simpanKeFile();
        printf("Anda berhasil meminjam alat: %s\n", daftarAlat[id - 1].nama);
    } else {
        printf("Alat '%s' tidak tersedia saat ini.\n", daftarAlat[id - 1].nama);
    }
}

// Kembalikan alat
void kembalikanAlat() {
    unsigned int id;
    semuaAlat();
    printf("\nMasukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &id);

    if (id < 1 || id > jumlahAlat) {
        printf("ID tidak valid!\n");
        return;
    }

    if (daftarAlat[id - 1].tersedia < daftarAlat[id - 1].jumlahUnit) {
        daftarAlat[id - 1].tersedia++;
        simpanKeFile();
        printf("Alat '%s' telah dikembalikan.\n", daftarAlat[id - 1].nama);
    } else {
        printf("Semua unit alat '%s' sudah tersedia.\n", daftarAlat[id - 1].nama);
    }
}

/*  MENU UTAMA  */

int main() {
    int pilihan;
    bacaDariFile();

    do {
        printf("1. Lihat Semua Alat\n");
        printf("2. Lihat Alat Tersedia\n");
        printf("3. Pinjam Alat\n");
        printf("4. Kembalikan Alat\n");
        printf("5. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: semuaAlat(); break;
            case 2: tersedia(); break;
            case 3: pinjamAlat(); break;
            case 4: kembalikanAlat(); break;
            case 5: printf("Terima kasih! Program selesai.\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);

    return 0;
}
