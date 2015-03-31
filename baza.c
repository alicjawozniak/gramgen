#include "baza.h"


void dodaj_haslo (struct s* skorow, char* ciag, char* wyst)
{
    struct s * p = skorow;
    while (p->nast != NULL)   //znalezienie nowej galezi
    {
        p = p->nast;
    }
    p->nast = malloc (sizeof *p->nast);
    p->nast->nast = NULL;    //init nast

    p->nast->prefiks = malloc ((strlen(ciag)+1)*sizeof(char)); //init tablicy dla bazy ngramu
    strcpy(p->nast->prefiks, ciag);
    p->nast->sufiksy = malloc(DLUGSLOWA*sizeof(char));  //init tablicy dla wystapienia
    strcpy(p->nast->sufiksy, wyst);
    p->nast->liczba_wyst = 1;  //init liczby wystapien
    p->nast->rozmiar = DLUGSLOWA;  //init rozmiaru
};

struct s* stworz_skorowidz (char* ciag, char* wyst)
{
    struct s* skorowidz = malloc(sizeof *skorowidz);
    skorowidz->prefiks = malloc((strlen(ciag)+2)*sizeof(char));
    strcpy (skorowidz->prefiks, ciag);
    skorowidz->liczba_wyst = 1;
    skorowidz->nast = NULL;
    skorowidz->rozmiar = DLUGSLOWA;
    skorowidz->sufiksy = malloc (DLUGSLOWA*sizeof(char));
    strcpy (skorowidz->sufiksy, wyst);
    return skorowidz;
};

void dodaj_wystapienie (struct s* p, char* slowo)
{
    if(p==NULL)
        printf("p jest null");
    powieksz_o_slowo(p);
    strcat(p->sufiksy, " ");
    strcat(p->sufiksy, slowo);
    p->liczba_wyst++;
}

struct s* znajdz_haslo (struct s* skorow, char* ciag)
{
    struct s* p = skorow;
    while (p != NULL)
    {
        if (strcmp(p->prefiks, ciag)==0)
            break;
        p = p->nast;
    }
    return p;
};

void powieksz_o_slowo (struct s* p)
{
    p->sufiksy = realloc(p->sufiksy, (p->rozmiar+DLUGSLOWA)*sizeof(char));
    p->rozmiar += DLUGSLOWA;
}

void wypisz_skorowidz(FILE* plik, struct s* skorowidz)
{
    struct s* p = skorowidz;
    while (p != NULL)
    {
        wypisz_linijke(plik, p);
        p = p->nast;
    }
}

void wypisz_linijke (FILE* plik, struct s * p)
{
    fprintf(plik, "%s %d %s\n", p->prefiks, p->liczba_wyst, p->sufiksy);
}
