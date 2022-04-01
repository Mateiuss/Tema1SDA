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

int insertWords(TH* h, char *str)
{
    char *parser = strtok(str, " .,-");
    parser = strtok(NULL, " .,-");

    while (parser) {
        if (strlen(parser) >= 3) {
            if (islower(parser[0])) {
                insertWord(&h->v[parser[0] - 'a'], parser);
            } else if (isupper(parser[0])) {
                insertWord(&h->v[parser[0] - 'A'], parser);
            }
        }

        parser = strtok(NULL, " .,-");
    }

    return 0;
}