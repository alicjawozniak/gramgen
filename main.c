#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"
#include "plik.h"
#include "ngram.h"


int main(int argc, char** argv)
{
    int rzad, ilosc_slow, ilosc_akapitow;
    char plik_baza[DLUGSLOWA];
    char plik_wyjscie[DLUGSLOWA];
    char plik_tekst [DLUGSLOWA];

    if (strcmp(argv[1], "-bgen") == 0)
    {
        if (strcmp(argv[2], "-s") == 1)
            ilosc_slow = atoi(argv[3]);
        if (strcmp(argv[4], "-a") == 1)
            ilosc_akapitow = atoi(argv[5]);
        if (strcmp(argv[6], "-n") == 1)
            rzad = atoi (argv[7]);
        if (strcmp(argv[8], "-b") == 1)
            strcpy(plik_baza, argv[9]);
        if (strcmp(argv[10], "-w") == 1)
            strcpy(plik_wyjscie, argv[11]);

        FILE* fbaza = fopen (plik_baza, "r");
        struct s* skorowidz = wczytaj_baze_z_pliku(plik_baza, rzad);
        napisz_tekst(plik_wyjscie, skorowidz, rzad, ilosc_slow, ilosc_akapitow);
    }

    else if (strcmp(argv[1], "-all") == 0)
    {
        if (strcmp(argv[2], "-s") == 1)
            ilosc_slow = atoi(argv[3]);
        if (strcmp(argv[4], "-a") == 1)
            ilosc_akapitow = atoi(argv[5]);
        if (strcmp(argv[6], "-n") == 1)
            rzad = atoi (argv[7]);
        if (strcmp(argv[8], "-w") == 1)
            strcpy(plik_wyjscie, argv[9]);
        if (strcmp(argv[10], "-p") == 1)
            strcpy(plik_tekst, argv[9]);

        FILE* fbaza = fopen ("baza.txt", "r+");
        struct s* skorowidz = czytaj_tekst_do_bazy(plik_tekst, rzad);
        zapisz_baze_do_pliku(fbaza, skorowidz);
        napisz_tekst(plik_wyjscie, skorowidz, rzad, ilosc_slow, ilosc_akapitow);
    }

    else if (strcmp(argv[1], "-stats") == 0)
    {
        if (strcmp(argv[2], "-n") == 1)
            rzad = atoi(argv[3]);
        if (strcmp(argv[4], "-p") == 1)
            strcpy(plik_baza, argv[5]);
        if (strcmp(argv[4], "-x") == 1)
            statystyki(plik_baza, rzad, argv[5]);

        statystyki_calosc (plik_baza, rzad);

    }

    return 0;

}
