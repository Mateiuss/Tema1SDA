/*DUDU Matei-Ioan - 313CB*/
#include "TLG.h"

// Caut daca exista deja cuvantul. Daca exista, ii incrementez aparitiile.
// Daca nu exista, caut daca mai exista cuvinte de lungimea lui, daca exista
// doar il adaug in lista deja existenta. Daca nu exista nici cuvinte de lungimea
// lui, creez lista cu lungimea aferenta si adaug cuvantul.
int insertWord(TLG *aL, char *str)
{
    int len = strlen(str);

    // Caut daca exista cuvantul, daca exista il incrementez direct in 
    // interiorul functiei "searchWord"
    if (searchWord(*aL, str, len)) {
        return 1;
    }

    // Aloc o celula pentru noul cuvant, in cazul in care cuvantul
    // nu a fost gasit
    TLC newWord = allocWord(str);
    if (!newWord) {
        return 0;
    }

    // Caut daca exista lista cu cuvinte de aceeasi lungime ca a cunvatului
    // pe care doresc sa il introduc. Daca exista, il inserez in acea lista
    TLG poz = searchLen(*aL, len);
    if (poz) {
        TLC wL = (TLC)poz->info;

        newWord->urm = wL;
        poz->info = newWord;

        return 1;
    }

    // In cazul in care nu am gasit lista cu cuvinte de aceeasi lungimea ca
    // a cuvantului pe care doresc sa il inserez creez o noua celula pentru
    // aceasta
    TLG newCell = allocCell(len);
    if (!newCell) {
        freeTCelulaC(newWord);
        return 0;
    }

    newCell->info = newWord;

    // Adaug noua celula in vectorul din tabela hash pe pozitia corespunzatoare
    addCell(aL, newCell);

    return 1;
}

// Functie de adaugare a unei celule pentru in lista corespunzatoare literei
// cu care incepe cuvantul. Totodata, adaug celula in ordine crescatoare dupa
// lungimea cu care incep cuvintele din aceasta, astfel, nemaifiind necesara
// o sortare ulterioara.
void addCell(TLG *aL, TLG newCell)
{
    // Daca lista este vida, adaug celula ca prim element
    if (!(*aL)) {
        *aL = newCell;
        return ;
    }

    TLG ant, p;

    int antLen = 2, len = newCell->len;

    for (p = *aL, ant = NULL; p != NULL; ant = p, p = p->urm) {
        int currLen = p->len;

        if (len > antLen && len < currLen) {
            break;
        }
    }

    // Daca p == NULL inseamna ca celula trebuie adaugata la sfarsit
    if (!p) {
        ant->urm = newCell;
        return ;
    }

    // Daca ant == NULL inseamna ca celula trebuie adaugata la inceput
    if (!ant) {
        newCell->urm = *aL;
        *aL = newCell;
        return ;
    }

    // Altfel, celula este adaugata undeva in interiorul listei, intre cele
    // doua celule care au cuvinte de lungime mai mica, respectiv mai mare
    // fata de lungimea cuvintelor continute in noua celula
    newCell->urm = ant->urm;
    ant->urm = newCell;
}

// Functie de alocare a unei celule ce va contine numai cuvinte de lungime len
TLG allocCell(int len)
{
    TLG aux = (TLG)malloc(sizeof(TCelulaG));
    if (!aux) {
        return NULL;
    }

    aux->info = aux->urm = NULL;
    aux->len = len;

    return aux;
}

// Functie de alocare a unei celule ce va contine informatiile despre cuvant
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

// Functie de cautare a unei celule ce contine cuvinte de lungime len.
// In cazul in care a fost gasita, functie returneaza adresa acesteia,
// altfel returneaza NULL
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

// Functie de cautare a unui cuvant. In cazul in care este gasit, i se
// vor incrementa numarul de aparitii si functia va returna 1, altfel
// va returna 0
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

// Functie de sortare ce primeste ca parametrii o lista de cuvinte si un
// pointer la o functie de comparare si sorteaza o lista de cuvinte
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

// Functie ce dezaloca memoria pentru o celula din lista de cuvinte
void freeTCelulaC(TLC L)
{
    free(((TLCuvant*)L->info)->cuv);
    free(L->info);
    free(L);
}

// Functie ce dezaloca memoria pentru o celula din lista ce contine lungimile
void freeTCelulaG(TLG L)
{
    freeTLC((TLC)L->info);
    free(L);
}

// Functie ce dezaloca memoria pentru lista de cuvinte
void freeTLC(TLC L)
{
    while (L) {
        TLC aux = L;
        L = L->urm;

        freeTCelulaC(aux);
    }
}

// Functie ce dezaloca memorie pentru lista ce contine lungimile
void freeTLG(TLG L)
{
    while (L) {
        TLG aux = L;
        L = L->urm;

        freeTLC((TLC)aux->info);
        free(aux);
    }
}