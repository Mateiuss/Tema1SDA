#include "TLG.h"

typedef int (*TFHash)(void*);

typedef struct thash {
    int M;
    TFHash fh;
    TLG *v;
} TH;

TH* initTH(int M, TFHash fp);
int insertWords(TH* h, char *str);
void deleteTH(TH* h);