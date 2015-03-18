#include "ngram.h"
#include "time.h"

char* dopisz_sufiks(struct s* skorowidz, char* zdanie, int rzad){
    struct s* p;
    int nr_wyst;
    int i = 0;
    char sufiks[1000];
    if ((p = znajdz_haslo(skorowidz, zdanie)) != NULL){
            nr_wyst = losuj_nr_wyst(p->liczba_wyst);
            while (i <= nr_wyst){
                sscanf(p->sufiksy, "%s", sufiks);
                i++;
            }
    }
    else
        printf("BLAAAD");
    return sufiks;
}

int losuj_nr_wyst (int liczba_wyst){
    srand(time(NULL));
    int a = (int) liczba_wyst*rand()/RAND_MAX;
    return a;
}
