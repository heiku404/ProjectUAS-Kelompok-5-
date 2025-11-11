#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ALAT 80
#define FILE_PATH "../data/alat.txt" 
#define ADMIN_PATH "../data/admin.txt"
#define USER_PATH "../data/user.txt"

// == STRUCT RESMI UNTUK SELURUH PROYEK ==
typedef struct {
    unsigned int id;
    char nama[100];
    char merek[100];
    char model[100];
    unsigned int tahunProduksi;
    unsigned int jumlahUnit;    // Total unit yang dimiliki
    unsigned int tersedia;      // Unit yang sedang ada di lab
} Alat;



int login(char *username, char *password);
void menu_admin();
void menu_user();


void muatDataAlat();
void simpanDataAlat();
Alat* dapatkanSemuaAlat(int* jumlah);
Alat* cariAlatById(unsigned int id);
int tambahAlat(unsigned int id, char* nama, char* merek, char* model, unsigned int tahun, unsigned int jumlah);
int hapusAlat(unsigned int id);
int pinjamAlat(unsigned int id);
int kembalikanAlat(unsigned int id);

#endif