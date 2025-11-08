#ifndef UTILS_H
#define UTILS_H
typedef struct {
    unsigned int id;
    char name[50];
    char merek[30];
    char model[30];
    unsigned int tahun_produksi;
    unsigned int jumlah_unit;
} Alat;

int fileKosong(const char *namaFile);
int cariAlatById(unsigned int id, Alat *alat);
void updateJumlahAlat(unsigned int id, int perubahan);
void hapusBarisById(const char *namaFile, unsigned int idHapus);

#endif