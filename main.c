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
    char c = *(char*)element;

    if (islower(c)) {
        return c - 'a';
    } else if (isupper(c)) {
        return c - 'A';
    }

    return -1; 
}

int compCuv(void *e1, void *e2)
{
    TLCuvant *a = (TLCuvant*)((TLC)e1)->info;
    TLCuvant *b = (TLCuvant*)((TLC)e2)->info;

    if (a->aparitii < b->aparitii) {
        return 1;
    }

    if (a->aparitii == b->aparitii && strcmp(a->cuv, b->cuv) > 0) {
        return 1;
    }

    return 0;
}

void Afisare1(TH *h)
{
    for (int i = 0; i < h->M; ++i) {
        if (h->v[i]) {
            printf("pos%d: ", i);
            for (TLG p = h->v[i]; p != NULL; p = p->urm) {
                printf("(%d:", p->len);
                
                for (TLC q = (TLC)p->info; q != NULL; q = q->urm) {
                    TLCuvant *info = (TLCuvant*)q->info;
                    if (!q->urm) {
                        printf("%s/%d", info->cuv, info->aparitii);
                    } else {
                        printf("%s/%d, ", info->cuv, info->aparitii);
                    }
                }
                printf(") ");
            }
            printf("\n");
        }
    }
}

void Afisare2(TH *h, int poz, int len)
{
    if (h->v[poz]) {
        for (TLG p = h->v[poz]; p != NULL; p = p->urm) {
            if (p->len == len) {
                printf("(%d:", p->len);
                
                for (TLC q = (TLC)p->info; q != NULL; q = q->urm) {
                    TLCuvant *info = (TLCuvant*)q->info;
                    if (!q->urm) {
                        printf("%s/%d", info->cuv, info->aparitii);
                    } else {
                        printf("%s/%d, ", info->cuv, info->aparitii);
                    }
                }
                printf(")\n");

                break;
            }
        }
    }
}

void Afisare3(TH *h, int aparitii)
{
    for (int i = 0; i < h->M; ++i) {
        if (h->v[i]) {
            int showPoz = 0;
            for (TLG p = h->v[i]; p != NULL; p = p->urm) {
                int showLen = 0;
                int enter = 0;

                for (TLC q = (TLC)p->info; q != NULL; q = q->urm) {
                    TLCuvant *info = (TLCuvant*)q->info;
                    if (info->aparitii <= aparitii) {
                        if (enter == 1) {
                            printf(", ");
                        }

                        if (!showPoz) {
                            showPoz = 1;
                            printf("pos%d: ",i);
                        }

                        if (!showLen) {
                            showLen = 1;
                            printf("(%d:", p->len);
                        }

                        printf("%s/%d", info->cuv, info->aparitii);

                        enter = 1;
                    }
                }

                if (showLen == 1) {
                    printf(") ");
                }
            }

            if (showPoz == 1) {
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
        int printed = 0;

        addNull(command);

        if (strstr(command, "insert")) {
            printed = 0;

            if(!insertWords(h, command, codHash)) {
                deleteTH(h);
                return -1;
            }
        } else if (strstr(command, "print")) {
            if (printed == 0) {
                sortTH(h, compCuv);
            }

            if (!strcmp(command, "print")) {
                Afisare1(h);
            } else {
                char *parser = strtok(command, " ");
                parser = strtok(NULL, " ");

                if (isalpha(*parser)) {
                    char c = *parser;
                    parser = strtok(NULL, " ");
                    int len = atoi(parser);

                    Afisare2(h, codHash((void*)&c), len);
                } else {
                    int aparitii = atoi(parser);

                    Afisare3(h, aparitii);
                }
            }
        }
    }

    deleteTH(h);

    return 0;
}