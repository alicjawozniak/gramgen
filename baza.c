#include "baza.h"


int dodaj_haslo (struct s* skorow, char* prefiks, char* sufiks)
{
    struct s * p = skorow;
    while (p->nast != NULL)   //znalezienie nowej galezi
    {
        p = p->nast;
    }
    p->nast = malloc (sizeof *p->nast);
    p->nast->nast = NULL;    //init nast

    p->nast->prefiks = malloc ((strlen(prefiks)+1)*sizeof(char)); //init tablicy dla bazy ngramu
    strcpy(p->nast->prefiks, prefiks);
    p->nast->sufiksy = malloc(DLUGSLOWA*sizeof(char));      //init tablicy dla sufiksapienia
    if (strlen(sufiks)>= DLUGSLOWA)
        return 0;
    strcpy(p->nast->sufiksy, sufiks);
    p->nast->liczba_wyst = 1;  //init liczby sufiksapien
    p->nast->rozmiar = DLUGSLOWA;  //init rozmiaru
    return 1;
};

struct s* stworz_skorowidz (char* prefiks, char* sufiks)
{
    struct s* skorowidz = malloc(sizeof *skorowidz);
    skorowidz->prefiks = malloc((strlen(prefiks)+2)*sizeof(char));
    strcpy (skorowidz->prefiks, prefiks);
    skorowidz->liczba_wyst = 1;
    skorowidz->nast = NULL;
    skorowidz->rozmiar = DLUGSLOWA;
    skorowidz->sufiksy = malloc (DLUGSLOWA*sizeof(char));
    strcpy (skorowidz->sufiksy, sufiks);
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

struct s* znajdz_haslo (struct s* skorow, char* prefiks)
{
    struct s* p = skorow;
    while (p != NULL)
    {
        if (strcmp(p->prefiks, prefiks)==0)
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

int wypisz_skorowidz(FILE* plik, struct s* skorowidz)
{
    if (plik == NULL)
        return 0;
    struct s* p = skorowidz;
    while (p != NULL)
    {
        wypisz_linijke(plik, p);
        p = p->nast;
    }
    return 1;
}

void wypisz_linijke (FILE* plik, struct s * p)
{
    fprintf(plik, "%s %d %s\n", p->prefiks, p->liczba_wyst, p->sufiksy);
}
