#ifndef _BAZA_H_
#define _BAZA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLUGSLOWA 30

struct s{
    char* prefiks;
    int liczba_wyst;
    char* sufiksy;
    int rozmiar;
    struct s* nast;
};

struct s * stworz_skorowidz(char* prefiks, char* sufiks);
int dodaj_haslo (struct s* skorow, char* prefiks, char* sufiks);
void dodaj_wystapienie (struct s* p, char* sufiks);
void powieksz_o_slowo (struct s* p);
struct s * znajdz_haslo (struct s* skorow, char* prefiks);
int wypisz_skorowidz (FILE* plik, struct s * skorowidz);
void wypisz_linijke (FILE* plik, struct s * p);
#endif // _BAZA_H_
