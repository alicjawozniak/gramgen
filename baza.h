#ifndef _BAZA_H_
#define _BAZA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLUGSLOWA 40
#define ILOSC_SUF 1000

struct s{
    char* prefiks;
    int liczba_wyst;
    char* sufiksy;
    int rozmiar;
    struct s* nast;
};

struct s * stworz_skorowidz(char* ciag, char* wyst);
void dodaj_haslo (struct s* skorow, char* ciag, char* wyst);
void dodaj_wystapienie (struct s* p, char* slowo);
void powieksz_o_slowo (struct s* p);
struct s * znajdz_haslo (struct s* skorow, char* ciag);
void wypisz_skorowidz (FILE* plik, struct s * skorowidz);
void wypisz_linijke (FILE* plik, struct s * p);
#endif // _BAZA_H_
