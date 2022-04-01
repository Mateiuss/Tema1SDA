#include "TLG.h"


// Caut daca exista deja cuvantul. Daca exista, ii incrementez aparitiile.
// Daca nu exista, caut daca mai exista cuvinte de lungimea lui, daca exista
// doar il adaug in lista deja existenta. Daca nu exista nici cuvinte de lungimea
// lui, creez lista cu lungimea aferenta si adaug cuvantul.
int insertWord(TLG *aL, char *str)
{ // TODO: sa fac free-urile necesare pentru alocari nereusite
    int len = strlen(str);

    // Caut daca exista cuvantul, daca exista il incrementez
    if (searchWord(*aL, str, len)) {
        return 1;
    }

    // Aloc o celula pentru noul cuvant, in cazul in care trebuie adaugat
    TLC newWord = allocWord(str);
    if (!newWord) {
        return 0;
    }

    TLG poz = searchLen(*aL, len);
    if (poz) {
        TLC wL = (TLC)poz->info;

        for (; wL->urm != NULL; wL = wL->urm);

        wL->urm = newWord;

        return 1;
    }

    TLG newCell = allocCell(len);
    if (!newCell) {
        return 0;
    }

    newCell->info = newWord;

    addCell(aL, newCell);

    return 1;
}

int addCell(TLG *aL, TLG newCell)
{
    if (!(*aL)) {
        *aL = newCell;
        return 1;
    }

    TLG ant, p, rez;

    int antLen = 2, len = newCell->len;

    for (p = *aL, ant = NULL; p != NULL; ant = p, p = p->urm) {
        int currLen = p->len;

        if (len > antLen && len < currLen) {
            rez = ant;
            break;
        }
    }

    if (!p) {
        ant->urm = newCell;
        return 1;
    }

    if (!ant) {
        newCell->urm = *aL;
        *aL = newCell;
        return 1;
    }

    newCell->urm = ant->urm;
    ant->urm = newCell;

    return 1;
}

TLG allocCell(int len)
{
    TLG aux = (TLG)malloc(sizeof(TCelulaG));
    if (!aux) {
        return NULL;
    }

    aux->info = aux->urm = NULL;
    aux->len = len;
}

TLC allocWord(char *str)
{
    TLC newWord = (TLC)malloc(sizeof(TCelulaC));
    if (!newWord) {
        return NULL;
    }  

    newWord->aparitii = 1;
    newWord->cuv = (char*)malloc(strlen(str) * sizeof(char));
    strcpy(newWord->cuv, str);
    newWord->urm = NULL;

    return newWord;
}

TLG searchLen(TLG L, int len)
{
    TLG p = L;

    for (; p != NULL; p = p->urm) {
        if (len == p->len) {
            return p;
        }
    }

    return NULL;
}

int searchWord(TLG L, char *str, int len)
{
    TLG p = L;
    for (; p != NULL; p = p->urm) {
        if (p->len == len) {
            TLC q = (TLC)p->info;
            for (; q != NULL; q = q->urm) {
                if (!strcmp(q->cuv, str)) {
                    ++q->aparitii;
                    return 1;
                }
            }
        }
    }

    return 0;
}