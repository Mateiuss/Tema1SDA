#include "THash.h"

TH* initTH(int M, TFHash fp)
{
    TH* h = (TH*)malloc(sizeof(TH));
    if (!h) {
        return NULL;
    }

    h->v = (TLG*)calloc(M, sizeof(TLG));
    if (!h->v) {
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fp;

    return h;
}

int insertWords(TH* h, char *str, int (*cod)(void*))
{
    int c;
    char *parser = strtok(str, " .,");
    parser = strtok(NULL, " .,");

    while (parser) {
        if (strlen(parser) >= 3) {
            if ((c = cod((void*)parser)) != -1) {
                int succes = insertWord(&h->v[c], parser);

                if (!succes) {
                    return 0;
                }
            }
        }

        parser = strtok(NULL, " .,");
    }

    return 1;
}

void sortTH(TH *h, int (*cmp)(void*, void*))
{
    for (int i = 0; i < h->M; ++i) {
        if (h->v[i]) {
            for (TLG p = h->v[i]; p != NULL; p = p->urm) {
                TLC info = (TLC)p->info;

                sortTLC(info, cmp);
            }
        }
    }
}

void deleteTH(TH* h)
{
    for (int i = 0; i < h->M; ++i) {
        if (h->v[i]) {
            freeTLG(h->v[i]);
        }
    }

    free(h->v);
    free(h);
}