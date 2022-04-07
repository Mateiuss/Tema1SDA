/*DUDU Matei-Ioan - 313CB*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Structura pentru celula ce contine void pointer la lista de cuvinte
// si lungimea comuna a acestora
typedef struct celulag {
    void *info;
    int len;
    struct celulag *urm;
} TCelulaG, *TLG;

// Structura pentru celula ce contine un void pointer la informatiile
// despre cuvant
typedef struct celulac {
    void *info;
    struct celulac *urm;
} TCelulaC, *TLC;

// Structura ce contine informatiile despre cuvant
typedef struct cuvant {
    int aparitii;
    char *cuv;
} TLCuvant;

int insertWord(TLG *aL, char *str);
TLC allocWord(char *str);
TLG searchLen(TLG L, int len);
int searchWord(TLG L, char *str, int len);
TLG allocCell(int len);
void addCell(TLG *aL, TLG newCell);
void freeTLG(TLG L);
void freeTLC(TLC L);
void freeTCelulaG(TLG L);
void freeTCelulaC(TLC L);
void sortTLC(TLC L, int (*cmp)(void*, void*));