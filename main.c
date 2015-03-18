#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"
#include "plik.h"
#include "ngram.h"


int main()
{
    FILE* baza = fopen("baza2.txt", "a+");
    struct s* skorowidz = czytaj_tekst_do_bazy("nicze.txt", 3);
    wypisz_skorowidz(baza, skorowidz);


    //printf ("znal: %s\n", dopisz_sufiks(skorowidz, "cztery", 2));
    return 0;

}
