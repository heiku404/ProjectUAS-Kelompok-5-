#include "../include/utils.h"

static void bersihkanBufferUser() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void semuaAlat_user() {
    int jumlah;
    Alat* daftar = dapatkanSemuaAlat(&jumlah); // Ambil data dari utils.c
    
    printf("\n=== DAFTAR SEMUA ALAT (Total: %d) ===\n", jumlah);
    if (jumlah == 0) {
        printf("Data kosong.\n");
        return;
    }
    printf("| %-3s | %-20s | %-15s | %-5s | %-8s |\n",
           "ID", "Nama", "Merek", "Tahun", "Tersedia");
    printf("|-----|----------------------|-----------------|-------|----------|\n");
    
    for (int i = 0; i < jumlah; i++) {
        printf("| %-3u | %-20s | %-15s | %-5u | %-8u |\n",
               daftar[i].id, daftar[i].nama, daftar[i].merek,
               daftar[i].tahunProduksi, daftar[i].tersedia);
    }
}

void tersedia_user() {
    int jumlah, jumlahTersedia = 0;
    Alat* daftar = dapatkanSemuaAlat(&jumlah); // Ambil data dari utils.c

    printf("\n=== ALAT YANG TERSEDIA ===\n");
    printf("| %-3s | %-20s | %-15s | %-5s | %-8s |\n",
           "ID", "Nama", "Merek", "Tahun", "Tersedia");
    printf("|-----|----------------------|-----------------|-------|----------|\n");

    for (int i = 0; i < jumlah; i++) {
        if (daftar[i].tersedia > 0) {
            printf("| %-3u | %-20s | %-15s | %-5u | %-8u |\n",
                   daftar[i].id, daftar[i].nama, daftar[i].merek,
                   daftar[i].tahunProduksi, daftar[i].tersedia);
            jumlahTersedia++;
        }
    }
    if (jumlahTersedia == 0) {
        printf("Tidak ada alat yang tersedia saat ini.\n");
    }
}

void pinjamAlat_user() {
    tersedia_user(); // Tampilkan dulu apa yg tersedia
    unsigned int id;
    printf("\nMasukkan ID alat yang ingin dipinjam: ");
    scanf("%u", &id); bersihkanBufferUser();
    
    // Panggil "mesin" utils.c
    pinjamAlat(id);
}

void kembalikanAlat_user() {
    unsigned int id;
    printf("\nMasukkan ID alat yang ingin dikembalikan: ");
    scanf("%u", &id); bersihkanBufferUser();

    // Panggil "mesin" utils.c
    kembalikanAlat(id);
}

void menu_user() {
    int pilihan;
    muatDataAlat(); // PENTING: Muat data saat menu user dimulai

    do {
        printf("\n===== Menu User =====\n");
        printf("1. Lihat Semua Alat\n");
        printf("2. Lihat Alat Tersedia\n");
        printf("3. Pinjam Alat\n");
        printf("4. Kembalikan Alat\n");
        printf("5. Keluar ke Login Utama\n");
        printf("Pilih menu: ");
        
        if (scanf("%d", &pilihan) != 1) {
            pilihan = 0; // Pilihan default
        }
        bersihkanBufferUser(); // Selalu bersihkan buffer

        switch (pilihan) {
            case 1: semuaAlat_user(); break;
            case 2: tersedia_user(); break;
            case 3: pinjamAlat_user(); break;
            case 4: kembalikanAlat_user(); break;
            case 5: printf("Keluar dari menu user...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);
}