#include "TLG.h"

typedef int (*TFHash)(void*);

typedef struct thash {
    int M;
    TFHash fh;
    TLG *v;
} TH;

TH* initTH(int M, TFHash fp);
void sortTH(TH *h, int (*cmp)(void*, void*));
int insertWords(TH* h, char *str, int (*cod)(void*));
void deleteTH(TH* h);