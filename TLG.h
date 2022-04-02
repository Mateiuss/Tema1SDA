#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct celulag {
    void *info;
    int len;
    struct celulag *urm;
} TCelulaG, *TLG;

typedef struct celulac {
    void *info;
    struct celulac *urm;
} TCelulaC, *TLC;

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