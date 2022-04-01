#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct celulag {
    void *info;
    int len;
    struct celulag *urm;
} TCelulaG, *TLG;

typedef struct cuvant {
    int aparitii;
    char *cuv;
    struct cuvant *urm;
}TCelulaC, *TLC;


int insertWord(TLG *aL, char *str);
TLC allocWord(char *str);
TLG searchLen(TLG L, int len);
int searchWord(TLG L, char *str, int len);
TLG allocCell(int len);
int addCell(TLG *aL, TLG newCell);