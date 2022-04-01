#include "THash.h"
#define MAX 100

void addNull(char *str)
{
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
}

int codHash (void *element)
{
    // De facut mai tarziu
    return 1;
}

void Afisare(TH *h)
{
    for (int i = 0; i < h->M; ++i) {
        if (h->v[i]) {
            printf("%c:\n", 'a' + i);
            for (TLG p = h->v[i]; p != NULL; p = p->urm) {
                printf("%d ", p->len);
                
                for (TLC q = (TLC)p->info; q != NULL; q = q->urm) {
                    printf("(%s si %d)", q->cuv, q->aparitii);
                }

                printf("\n");
            }
        }
    }
}

int main()
{
    int M = 'z' - 'a' + 1;
    TH *h = initTH(M, codHash);
    if (!h)
    {
        printf("Nu s-a putut aloca memorie pentru tabela hash!\n");
        return -1;
    }
    
    char command[MAX];

    while (fgets(command, MAX, stdin)) {
        addNull(command);

        if (strstr(command, "insert")) {
            insertWords(h, command);
        }
    }

    Afisare(h);

    deleteTH(h);

    return 0;
}