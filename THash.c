/*DUDU Matei-Ioan - 313CB*/
#include "THash.h"

// Functie ce aloca memorie pentru tabela hash
TH* initTH(int M, TFHash fp)
{
    TH* h = (TH*)malloc(sizeof(TH));
    if (!h) {
        return NULL;
    }

    h->v = (TLG*)calloc(M + 1, sizeof(TLG));
    if (!h->v) {
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fp;

    return h;
}

// Functie ce prelucreaza un sir si adauga cuvintele continute de acesta in
// tabela hash
int insertWords(TH* h, char *str, int (*cod)(void*))
{
    int c;
    char *parser = strtok(str, " .,");
    parser = strtok(NULL, " .,");

    while (parser) {
        if (strlen(parser) >= 3 && (c = cod((void*)parser)) != -1) {
            if (!insertWord(&h->v[c], parser)) {
                return 0;
            }
        }

        parser = strtok(NULL, " .,");
    }

    return 1;
}

// Functie de sortare a tuturor listelor de cuvinte din tabela hash
void sortTH(TH *h, int (*cmp)(void*, void*))
{
    for (int i = 0; i <= h->M; ++i) {
        if (h->v[i]) {
            for (TLG p = h->v[i]; p != NULL; p = p->urm) {
                TLC info = (TLC)p->info;

                sortTLC(info, cmp);
            }
        }
    }
}

// Functie care elibereaza toata memoria alocata tabelei hash
void deleteTH(TH* h)
{
    for (int i = 0; i <= h->M; ++i) {
        if (h->v[i]) {
            freeTLG(h->v[i]);
        }
    }

    free(h->v);
    free(h);
}