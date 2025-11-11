#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 50

char kataunik[MAX_WORDS][MAX_WORD_LEN]; 
int hitungkata = 0; 
char judul[1024] = ""; 

int pengecekan(const char* word) {
    for (int i = 0; i < hitungkata; i++) {
        if (strcmp(word, kataunik[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int main(){
FILE* lagu = fopen("lirik.txt", "r");
    
    if (lagu == NULL) {
        printf("Error\n");
        return 1; 
    }
    
    char line[1024]; 
    const char buang[] = " .,?[]:-\n"; 
    int barispertama = 1; 

    while (fgets(line, sizeof(line), lagu) != NULL) {
        
        if (barispertama) {
            strcpy(judul, line);
            barispertama = 0;
            continue; 
        }
        
        char *token = strtok(line, buang);
        while (token != NULL) {
            for (int i = 0; token[i] != '\0'; i++) {
                token[i] = tolower(token[i]); 
            }
            if (strlen(token) > 0) { 
                if (pengecekan(token)) {
                    if (hitungkata < MAX_WORDS) {
                        strcpy(kataunik[hitungkata], token); 
                        hitungkata++; 
                    }
                }
            }
            token = strtok(NULL, buang);
        }
    }
    fclose(lagu);

    FILE* output = fopen("kosa-kata.txt", "w");
    if (output == NULL) {
        printf("Error\n");
        return 1;
    }
    fprintf(output, "%s", judul); 
    for (int i = 0; i < hitungkata; i++) {
        fprintf(output, "%s===\n", kataunik[i]); 
    }  
printf("Sekarang kak piwa bisa membaca kosa kata dari lirik lagu\n");
printf("Total kata unik yang ditemukan: %d\n", hitungkata);
return 0;


}