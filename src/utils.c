#include "../include/utils.h"

int fileKosong (const char*namaFile){
    FILE *fp = fopen ("alat.txt", "r");
    if (fp == NULL){
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    if (size == 0)
        return 1;  // kosong
    else
        return 0;  // ada isi
}

int cariAlatById(unsigned int id, Alat *out) {
    FILE *fp = fopen("alat.txt", "r");
    if (fp == NULL){
        printf("file tidak ditemukan");
        return 0;
    }
    char line[256];
    while(fgets(line,sizeof(line), fp)!= NULL){
        unsigned int tid, ttahun, tjumlah;
        char tnama[50], tmerek[30], tmodel[30];

        int parsed = sscanf(line, "%u|%49[^|]|%29[^|]|%29[^|]|%u|%u",&tid, tnama, tmerek, tmodel, &ttahun, &tjumlah);
        if (parsed == 6 && tid == id){
            out->id = tid;
            strcpy(out->name, tnama);
            strcpy(out->merek, tmerek);
            strcpy(out->model, tmodel);
            out->tahun_produksi = ttahun;
            out->jumlah_unit = tjumlah;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int updateJumlahAlat(unsigned int id, int perubahan){
        FILE*fp = fopen ("alat.txt", "r");
        if (fp == NULL){
            return 0;
        }

        FILE*temp = fopen("temp.txt", "w");
        if (temp == NULL){
            fclose(fp);
            return 0;
        }
        char line[256];
        int found = 0;

        while(fgets(line, sizeof(line), fp)!=NULL){
            unsigned int tid, ttahun, tjumlah;
            char tnama[50], tmerek[30], tmodel[30];

            int parsed= sscanf(line, "%u|%49[^|]|%29[^|]|%29[^|]|%u|%u",&tid, tnama, tmerek, tmodel, &ttahun, &tjumlah);
            if (parsed != 6) continue;
            if (tid==id){
                long newJumlah = (long)tjumlah+perubahan;
                if (newJumlah < 0){
                    printf("jumlah gaboleh negatif");
                    newJumlah= tjumlah;
                } else{
                    tjumlah = (unsigned int)newJumlah;
                    found=1;
                }
            }
            fprintf(temp, "%u|%s|%s|%s|%u|%u\n",
                tid, tnama, tmerek, tmodel, ttahun, tjumlah);
        }
        fclose(fp);
        fclose(temp);
        remove("alat.txt");
        rename("temp.txt", "alat.txt");
        return found ? 1 : 0;
    }

void hapusBarisById(const char *namaFile, unsigned int idHapus) {
    FILE *fp = fopen(namaFile, "r");
    if (fp == NULL) {
        printf("File tidak ditemukan.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Gagal membuat file sementara.\n");
        fclose(fp);
        return;
    }
        char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        unsigned int tid, ttahun, tjumlah;
        char tnama[50], tmerek[30], tmodel[30];

        int parsed = sscanf(line, "%u|%49[^|]|%29[^|]|%29[^|]|%u|%u",
                            &tid, tnama, tmerek, tmodel, &ttahun, &tjumlah);

        if (parsed != 6) continue; // lewati baris rusak

        if (tid == idHapus) {
            found = 1;
            continue; // lewati baris ini (hapus)
        }

        fprintf(temp, "%u|%s|%s|%s|%u|%u\n",
                tid, tnama, tmerek, tmodel, ttahun, tjumlah);
    }
    fclose(fp);
    fclose(temp);

    remove(namaFile);              // hapus file lama
    rename("temp.txt", namaFile);  // ganti dengan file baru
     if (found)
        printf("Data dengan ID %u berhasil dihapus.\n", idHapus);
    else
        printf("Data dengan ID %u tidak ditemukan.\n", idHapus);
}