#include "../include/utils.h"

static void bersihkanBufferAdmin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void tampilkan_alat_admin() {
    int jumlah;
    Alat* daftar = dapatkanSemuaAlat(&jumlah); 

    printf("\n================================= Daftar Alat Lab (Total: %d) ================================\n", jumlah);
    if (jumlah == 0) {
        printf("Data kosong.\n");
        return;
    }
    
    printf("| %-3s | %-20s | %-15s | %-15s | %-5s | %-5s | %-8s |\n",
           "ID", "Nama", "Merek", "Model", "Tahun", "Total", "Tersedia");
    printf("|-----|----------------------|-----------------|-----------------|-------|-------|----------|\n");

    for (int i = 0; i < jumlah; i++) {
        printf("| %-3u | %-20s | %-15s | %-15s | %-5u | %-5u | %-8u |\n",
               daftar[i].id, daftar[i].nama, daftar[i].merek,
               daftar[i].model, daftar[i].tahunProduksi,
               daftar[i].jumlahUnit, daftar[i].tersedia);
    }
}

void tambah_alat_admin() {
    unsigned int id, tahun, jumlah;
    char nama[100], merek[100], model[100];

    printf("Masukkan ID Alat: ");
    scanf("%u", &id); bersihkanBufferAdmin();
    
    printf("Masukkan Nama Alat: ");
    scanf(" %99[^\n]", nama); bersihkanBufferAdmin();
    
    printf("Masukkan Merek Alat: ");
    scanf(" %99[^\n]", merek); bersihkanBufferAdmin();
    
    printf("Masukkan Model Alat: ");
    scanf(" %99[^\n]", model); bersihkanBufferAdmin();
    
    printf("Masukkan Tahun Produksi: ");
    scanf("%u", &tahun); bersihkanBufferAdmin();
    
    printf("Masukkan Jumlah Unit: ");
    scanf("%u", &jumlah); bersihkanBufferAdmin();

    if (tambahAlat(id, nama, merek, model, tahun, jumlah)) {
        printf("Data alat berhasil ditambahkan.\n");
    } else {
        printf("Gagal menambahkan alat (cek error di atas).\n");
    }
}

void edit_alat_admin() {
    unsigned int id;
    printf("Masukkan ID Alat yang akan diedit: ");
    scanf("%u", &id); bersihkanBufferAdmin();

    Alat* alat = cariAlatById(id);
    if (alat == NULL) {
        printf("Error: ID %u tidak ditemukan!\n", id);
        return;
    }

    printf("Data saat ini: [%s], [%s], [%s], [%u], [%u], Tersedia [%u]\n", 
           alat->nama, alat->merek, alat->model, alat->tahunProduksi, alat->jumlahUnit, alat->tersedia);
    printf("Masukkan data baru (tekan Enter untuk skip):\n");

    char buffer[100];

    printf("Nama: ");
    fgets(buffer, 99, stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(alat->nama, buffer);

    printf("Merek: ");
    fgets(buffer, 99, stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(alat->merek, buffer);

    printf("Model: ");
    fgets(buffer, 99, stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) strcpy(alat->model, buffer);

    printf("Tahun: ");
    fgets(buffer, 99, stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) alat->tahunProduksi = (unsigned int)atoi(buffer);

    printf("Jumlah Total Unit: ");
    fgets(buffer, 99, stdin); buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        unsigned int jumlahBaru = (unsigned int)atoi(buffer);
        // Hitung selisih untuk menyesuaikan 'tersedia'
        int selisih = (int)jumlahBaru - (int)alat->jumlahUnit;
        alat->jumlahUnit = jumlahBaru;
        int tersediaBaru = (int)alat->tersedia + selisih;
        if (tersediaBaru < 0) tersediaBaru = 0;
        if (tersediaBaru > (int)alat->jumlahUnit) tersediaBaru = (int)alat->jumlahUnit;
        alat->tersedia = (unsigned int)tersediaBaru;
        printf("Jumlah unit diupdate, ketersediaan disesuaikan menjadi: %u\n", alat->tersedia);
    }
    
    simpanDataAlat(); // Simpan perubahan ke file
    printf("Data alat berhasil diupdate.\n");
}

void hapus_alat_admin() {
    unsigned int id;
    printf("Masukkan ID Alat yang akan dihapus: ");
    scanf("%u", &id); bersihkanBufferAdmin();

    hapusAlat(id); 
}

void menu_admin() {
    int pilihan;
    muatDataAlat(); 

    do {
        printf("\n===== Menu Admin =====\n");
        printf("1. Tampilkan Semua Alat\n");
        printf("2. Tambah Alat Baru\n");
        printf("3. Edit Alat\n");
        printf("4. Hapus Alat\n");
        printf("5. Keluar ke Login Utama\n");
        printf("Pilih menu: ");
        
        if (scanf("%d", &pilihan) != 1) {
            pilihan = 0; // Pilihan default jika input bukan angka
        }
        bersihkanBufferAdmin(); // Selalu bersihkan buffer

        switch (pilihan) {
            case 1: tampilkan_alat_admin(); break;
            case 2: tambah_alat_admin(); break;
            case 3: edit_alat_admin(); break;
            case 4: hapus_alat_admin(); break;
            case 5: printf("Keluar dari menu admin...\n"); break;
            default: printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 5);
}