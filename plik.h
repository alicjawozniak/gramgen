#ifndef _PLIK_H_
#define _PLIK_H_
#include "baza.h"

void zapisz_baze_do_pliku (char* plik, struct s* skorowidz);
struct s* wczytaj_baze_z_pliku (char* plik, int rzad);
int wczytaj_linijke(FILE* fp, struct s* p, int rzad);

struct s* czytaj_tekst_do_bazy (char* plik, int rzad);

#endif // _PLIK_H_
