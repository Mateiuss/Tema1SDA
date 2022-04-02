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
        freeTCelulaC(newWord);
        return 0;
    }

    newCell->info = newWord;

    addCell(aL, newCell);

    return 1;
}

void addCell(TLG *aL, TLG newCell)
{
    if (!(*aL)) {
        *aL = newCell;
        return ;
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
        return ;
    }

    if (!ant) {
        newCell->urm = *aL;
        *aL = newCell;
        return ;
    }

    newCell->urm = ant->urm;
    ant->urm = newCell;
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

    TLCuvant *info = (TLCuvant*)malloc(sizeof(TLCuvant));
    if (!info) {
        free(newWord);
        return NULL;
    }

    info->aparitii = 1;
    info->cuv = (char*)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(info->cuv, str);

    newWord->urm = NULL;
    newWord->info = (void*)info;

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
                TLCuvant *info = (TLCuvant*)q->info;
                if (!strcmp(info->cuv, str)) {
                    ++info->aparitii;
                    return 1;
                }
            }
        }
    }

    return 0;
}

void sortTLC(TLC L, int (*cmp)(void*, void*))
{
    TLC p = L, q;

    for (; p != NULL; p = p->urm) {
        for (q = p->urm; q != NULL; q = q->urm) {
            if (cmp((void*)p, (void*)q)) {
                void * aux = p->info;
                p->info = q->info;
                q->info = aux;
            }
        }
    }
}

void freeTCelulaC(TLC L)
{
    free(((TLCuvant*)L->info)->cuv);
    free(L->info);
    free(L);
}

void freeTCelulaG(TLG L)
{
    freeTLC((TLC)L->info);
    free(L);
}

void freeTLC(TLC L)
{
    while (L) {
        TLC aux = L;
        L = L->urm;

        freeTCelulaC(aux);
    }
}

void freeTLG(TLG L)
{
    while (L) {
        TLG aux = L;
        L = L->urm;

        freeTLC((TLC)aux->info);
        free(aux);
    }
}