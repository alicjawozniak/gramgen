#ifndef _NGRAM_H_
#define _NGRAM_H_
#include "baza.h"

char* dopisz_sufiks(FILE* fp, struct s* skorowidz, char* zdanie, int rzad);
int losuj_nr_wyst (int liczba_wyst);
int napisz_akapit (FILE* fp, struct s* skorowidz, int rzad, int ilosc_slow);
char* losuj_prefiks (FILE* fp, struct s* skorowidz);
int napisz_tekst (char* plik, struct s* skorowidz, int rzad, int suma_slow, int ilosc_akapitow);

#endif // _NGRAM_H_
