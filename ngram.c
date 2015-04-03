#include "ngram.h"
#include <math.h>

char* dopisz_sufiks(FILE* plik, struct s* skorowidz, char* zdanie, int rzad)
{
    struct s* p;
    int nr_wyst;
    int i = 0;
    int j = 0;
    int liczba_spacji = 0;
    char sufiks[1000];
    if ((p = znajdz_haslo(skorowidz, zdanie)) != NULL)
    {
        nr_wyst = losuj_nr_wyst(p->liczba_wyst);
        while (liczba_spacji < nr_wyst)
        {
            if (p->sufiksy[i] == ' ')
                liczba_spacji++;
            i++;
        }
        while (p->sufiksy[i]!= ' ' && p->sufiksy[i] != '\0')
        {
            sufiks[j] = p->sufiksy[i];
            i++;
            j++;
        }
        sufiks[j] = '\0';
    }
    else
        return NULL;
    fseek(plik, 0, SEEK_END);
    fprintf(plik, "%s ", sufiks);
    return sufiks;
}

int losuj_nr_wyst (int liczba_wyst)
{
    int a = rand()%liczba_wyst;
    return a;
}

int napisz_akapit (FILE* fp, struct s* skorowidz, int rzad, int ilosc_slow)
{
    int wypisane_slowa = 0;
    ilosc_slow -= (rzad-1);
    fpos_t pozycja;
    fgetpos(fp, &pozycja);
    fprintf(fp, "\t");
    losuj_prefiks(fp, skorowidz);
    wypisane_slowa += 2;
    fsetpos(fp, &pozycja);
    int i = 0, j = 0;
    char temp[1000] = "";
    char prefiks[1000] = "";

    while (j < ilosc_slow)
    {
        while (i < rzad-1)
        {
            fscanf(fp, "%s", temp);
            strcat(prefiks, temp);
            if (i == 0)
                fgetpos(fp, &pozycja);
            if (i<rzad-2)
                strcat(prefiks, " ");
            i++;
        };
        if (dopisz_sufiks(fp, skorowidz, prefiks, rzad) != NULL)
            wypisane_slowa++;
        else
            return wypisane_slowa;
        i = 0;
        strcpy(prefiks, "");
        strcpy(temp, "");
        fsetpos(fp, &pozycja);
        j++;
    }
    fseek(fp, 0, SEEK_END);
    fprintf(fp, "\n");
    return wypisane_slowa;
}

char* losuj_prefiks (FILE* fp, struct s* skorowidz)
{
    struct s* p = skorowidz;
    int a = rand();
    int i = 0;
    while (i < a)
    {
        p = p->nast;
        if (p == NULL)
            p = skorowidz;
        i++;
    }
    fprintf(fp, "%s ", p->prefiks);
    return p->prefiks;
}

int napisz_tekst (char* plik, struct s* skorowidz, int rzad, int suma_slow, int ilosc_akapitow)
{
    int dlug_akapitu = suma_slow/ilosc_akapitow + 1;
    FILE* fp = fopen (plik, "r+");
    if (fp == NULL)
    {
        printf("Nie znaleziono pliku wyjsciowego.\n");
        return 0;
    }
    while ( suma_slow >= dlug_akapitu)
    {
        fseek(fp, 0, SEEK_END);
        suma_slow -= napisz_akapit(fp, skorowidz, rzad, dlug_akapitu);
    }
    fseek(fp, 0, SEEK_END);
    if (suma_slow != 0)
        napisz_akapit(fp, skorowidz, rzad, suma_slow);
    return 1;
}

