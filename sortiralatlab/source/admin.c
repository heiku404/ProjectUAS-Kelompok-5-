#include "../include/utils.h"

void menu_admin(){
    int pilihan;
    do{
        printf("=================== Menu Admin ===================\n");
        printf("1. Tampilkan List Alat Lab Yang Tersedia\n");
        printf("2. Tampilkan List Alat Lab Yang Sedang Dipinjam\n");
        printf("3. Edit List Alab Lab\n");
        printf("4. Keluar\n");
        printf("Pilih Menu: ");
        scanf("%d", &pilihan);

        switch(pilihan){
        case 1:
        view_list();
        break;

        case 2:
        view_list_pinjam();
        break;

        case 3:
        edit_list();
        break;

        case 4: 
        printf("Keluar dari menu admin...\n");
        break;
        
        default:
        printf("Input invalid\n");
        break;
        }
    }while(pilihan != 4);
}

void edit_list() {
    int pilihan;
    printf("\n========== Menu Edit Alat Lab ==========\n");
    printf("1. Tambah Alat Lab Baru\n");
    printf("2. Hapus Alat Lab\n");
    printf("3. Update Data Alat Lab\n");
    printf("4. Kembali ke Menu Utama\n");
    printf("Pilih Menu: ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            add_alat();
            break;
        case 2:
            delete_alat();
            break;
        case 3:
            update_alat();
            break;
        case 4:
            printf("Kembali ke menu admin...\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
    }
}

void add_alat() {
    alat_lab alat_baru; 

    printf("\n--- Menambah Alat Lab Baru ---\n");
    printf("Masukkan ID Alat: ");
    scanf("%u", &alat_baru.id_alat); 

    printf("Masukkan Nama Alat: ");
    scanf(" %[^\n]", alat_baru.nama_alat); 

    printf("Masukkan Merek Alat: ");
    scanf(" %[^\n]", alat_baru.merk_alat);

    printf("Masukkan Model Alat: ");
    scanf(" %[^\n]", alat_baru.model_alat);

    printf("Masukkan Tahun Produksi: ");
    scanf("%u", &alat_baru.tahun_produksi_alat);

    printf("Masukkan Jumlah Stok: ");
    scanf("%u", &alat_baru.jumlah_alat);

    FILE *fptr = fopen("../data/listbarang.txt", "a");
    if (fptr == NULL) {
        printf("Program Gagal: Gagal membuka file listbarang.txt!\n");
        return;
    }

    fprintf(fptr, "\n%u;%s;%s;%s;%u;%u",
            alat_baru.id_alat,
            alat_baru.nama_alat,
            alat_baru.merk_alat,
            alat_baru.model_alat,
            alat_baru.tahun_produksi_alat,
            alat_baru.jumlah_alat);

    fclose(fptr);

    printf("\nProgram Berhasil: Alat baru telah ditambahkan ke listbarang.txt.\n");
}

void delete_alat() {
    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;
    unsigned int id_hapus;
    int i, index_ditemukan = -1; 

    load_alat(daftar_alat, &jumlah_alat, "../data/listbarang.txt");

    if (jumlah_alat == 0) {
        printf("\nFile list_barang.txt kosong, tidak ada yang bisa dihapus.\n");
        return;
    }

    printf("\n--- Daftar Alat Saat Ini ---");
    view_list(); 

    printf("Masukkan ID Alat yang ingin Anda hapus: ");
    scanf("%u", &id_hapus);

    for (i = 0; i < jumlah_alat; i++) {
        if (daftar_alat[i].id_alat == id_hapus) {
            index_ditemukan = i; 
            break; 
        }
    }

    if (index_ditemukan == -1) {
        printf("\nProgram Gagal: ID Alat %u tidak ditemukan.\n", id_hapus);
        return; 
    }

    FILE *fptr = fopen("../data/listbarang.txt", "w");
    if (fptr == NULL) {
        printf("Program Gagal: Gagal membuka file listbarang.txt!\n");
        return;
    }

    int baris_pertama_ditulis = 1; 

    for (i = 0; i < jumlah_alat; i++) {
        
        if (i == index_ditemukan) { 
            continue; 
        }
        if (baris_pertama_ditulis == 1) {
            baris_pertama_ditulis = 0; 
        } else {
            fprintf(fptr, "\n");
        }

        fprintf(fptr, "%u;%s;%s;%s;%u;%u",
                daftar_alat[i].id_alat,
                daftar_alat[i].nama_alat,
                daftar_alat[i].merk_alat,
                daftar_alat[i].model_alat,
                daftar_alat[i].tahun_produksi_alat,
                daftar_alat[i].jumlah_alat);
    }

    fclose(fptr);

    printf("\nBERHASIL: Alat dengan ID %u telah dihapus dari listbarang.txt.\n", id_hapus);
}

void update_alat() {
    alat_lab daftar_alat[maxSize];
    int jumlah_alat = 0;
    unsigned int id_update;
    int i, index_ditemukan = -1;

    load_alat(daftar_alat, &jumlah_alat, "../data/listbarang.txt");

    if (jumlah_alat == 0) {
        printf("\nFile list barang kosong, tidak ada yang bisa di-update.\n");
        return;
    }

    printf("\n--- Daftar Alat Saat Ini ---");
    view_list(); 

    printf("Masukkan ID Alat yang ingin Anda update: ");
    scanf("%u", &id_update);

    for (i = 0; i < jumlah_alat; i++) {
        if (daftar_alat[i].id_alat == id_update) {
            index_ditemukan = i; 
            break; 
        }
    }

    if (index_ditemukan == -1) {
        printf("\nError: ID Alat %u tidak ditemukan.\n", id_update);
        return; 
    }

    printf("\n--- Masukkan Data Baru untuk ID %u ---\n", id_update);
    
    printf("Masukkan Nama Alat Baru: ");
    scanf(" %[^\n]", daftar_alat[index_ditemukan].nama_alat); 

    printf("Masukkan Merek Alat Baru: ");
    scanf(" %[^\n]", daftar_alat[index_ditemukan].merk_alat);

    printf("Masukkan Model Alat Baru: ");
    scanf(" %[^\n]", daftar_alat[index_ditemukan].model_alat);

    printf("Masukkan Tahun Produksi Baru: ");
    scanf("%u", &daftar_alat[index_ditemukan].tahun_produksi_alat);

    printf("Masukkan Jumlah Stok Baru: ");
    scanf("%u", &daftar_alat[index_ditemukan].jumlah_alat);
    
    FILE *fptr = fopen("../data/listbarang.txt", "w");
    if (fptr == NULL) {
        printf("Error: Gagal membuka file listbarang.txt!\n");
        return;
    }

    for (i = 0; i < jumlah_alat; i++) {
        if (i > 0) {
            fprintf(fptr, "\n");
        }

        fprintf(fptr, "%u;%s;%s;%s;%u;%u",
                daftar_alat[i].id_alat,
                daftar_alat[i].nama_alat,
                daftar_alat[i].merk_alat,
                daftar_alat[i].model_alat,
                daftar_alat[i].tahun_produksi_alat,
                daftar_alat[i].jumlah_alat);
    }

    fclose(fptr);

    printf("\nBERHASIL: Alat dengan ID %u telah di-update.\n", id_update);
}