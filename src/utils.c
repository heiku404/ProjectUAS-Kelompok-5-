#include "../include/utils.h"

static Alat daftarAlat[MAX_ALAT];
static int jumlahAlat = 0;

void muatDataAlat() {
    FILE *file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        printf("Gagal membuka %s. File mungkin belum ada.\n", FILE_PATH);
        jumlahAlat = 0;
        return;
    }

    jumlahAlat = 0;
    while (jumlahAlat < MAX_ALAT &&
           fscanf(file, "%u;%99[^;];%99[^;];%99[^;];%u;%u;%u\n",
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

void simpanDataAlat() {
    FILE *file = fopen(FILE_PATH, "w");
    if (file == NULL) {
        printf("FATAL ERROR: Gagal menyimpan data ke %s!\n", FILE_PATH);
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

Alat* dapatkanSemuaAlat(int* jumlah) {
    *jumlah = jumlahAlat;
    return daftarAlat;
}

Alat* cariAlatById(unsigned int id) {
    for (int i = 0; i < jumlahAlat; i++) {
        if (daftarAlat[i].id == id) {
            return &daftarAlat[i]; // Kembalikan alamat (pointer)
        }
    }
    return NULL; // Tidak ditemukan
}

int tambahAlat(unsigned int id, char* nama, char* merek, char* model, unsigned int tahun, unsigned int jumlah) {
    if (cariAlatById(id) != NULL) {
        printf("Error: ID %u sudah ada!\n", id);
        return 0; // Gagal (ID duplikat)
    }
    if (jumlahAlat >= MAX_ALAT) {
        printf("Error: Database penuh!\n");
        return 0; // Gagal (Database penuh)
    }

    Alat* alatBaru = &daftarAlat[jumlahAlat];
    alatBaru->id = id;
    strcpy(alatBaru->nama, nama);
    strcpy(alatBaru->merek, merek);
    strcpy(alatBaru->model, model);
    alatBaru->tahunProduksi = tahun;
    alatBaru->jumlahUnit = jumlah;
    alatBaru->tersedia = jumlah; // Saat baru ditambah, semua tersedia

    jumlahAlat++;
    simpanDataAlat(); // Langsung simpan ke file
    return 1; // Sukses
}

int hapusAlat(unsigned int id) {
    int index = -1;
    for (int i = 0; i < jumlahAlat; i++) {
        if (daftarAlat[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: ID %u tidak ditemukan!\n", id);
        return 0; // Gagal (tidak ditemukan)
    }

    // Geser semua elemen setelahnya ke kiri
    for (int i = index; i < jumlahAlat - 1; i++) {
        daftarAlat[i] = daftarAlat[i + 1];
    }

    jumlahAlat--;
    simpanDataAlat();
    printf("Data dengan ID %u berhasil dihapus.\n", id);
    return 1; // Sukses
}

int pinjamAlat(unsigned int id) {
    Alat* alat = cariAlatById(id);
    if (alat == NULL) {
        printf("Error: ID %u tidak ditemukan!\n", id);
        return 0;
    }
    if (alat->tersedia == 0) {
        printf("Maaf, alat '%s' sedang habis dipinjam.\n", alat->nama);
        return 0;
    }

    alat->tersedia--;
    simpanDataAlat();
    printf("Anda berhasil meminjam: %s (Tersisa: %u)\n", alat->nama, alat->tersedia);
    return 1;
}

int kembalikanAlat(unsigned int id) {
    Alat* alat = cariAlatById(id);
    if (alat == NULL) {
        printf("Error: ID %u tidak ditemukan!\n", id);
        return 0;
    }
    if (alat->tersedia >= alat->jumlahUnit) {
        printf("Alat '%s' sudah lengkap (%u unit). Pengembalian ditolak.\n", alat->nama, alat->jumlahUnit);
        return 0; // Tidak bisa mengembalikan lebih
    }

    alat->tersedia++;
    simpanDataAlat();
    printf("Alat '%s' telah dikembalikan. (Tersedia: %u)\n", alat->nama, alat->tersedia);
    return 1;
}