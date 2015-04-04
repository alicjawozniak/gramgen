#include "plik.h"

int zapisz_baze_do_pliku (char* plik, struct s* skorowidz)
{
    FILE* fp = fopen(plik, "r+");
    if (fp == NULL)
    {
        printf("Nie znaleziono pliku bazy.\n");
        return 0;
    }
    wypisz_skorowidz(fp, skorowidz);
    fclose(fp);
    return 1;
}

struct s* wczytaj_baze_z_pliku (char* plik, int rzad)
{
    FILE* fp = fopen(plik, "r");
    if( fp == NULL)
    {
        printf("Nie znaleziono pliku bazy.\n");
        return NULL;
    }
    struct s* skorowidz = malloc (sizeof *skorowidz);
    struct s* p = skorowidz;

    wczytaj_linijke(fp, p, rzad);
    p->nast = malloc(sizeof *p->nast);
    while (wczytaj_linijke(fp, p->nast, rzad) != -1)
    {
        p->nast->nast = malloc (sizeof *p->nast);
        p = p->nast;
    }
    p->nast = NULL;
    return skorowidz;
};

int wczytaj_linijke(FILE* fp, struct s* p, int rzad)
{
    char bufor[DLUGSLOWA];
    char k;
    int i = 0;
    p->prefiks = malloc(DLUGSLOWA*rzad*sizeof(char));
    strcpy (p->prefiks, "");
    while (i < rzad - 1)
    {
        if (fscanf(fp, "%s", bufor) != 1) return -1;
        strcat(p->prefiks, bufor);
        if (i<rzad -2)
            strcat(p->prefiks, " ");
        i++;
    };
    fscanf(fp, "%d", &i);
    p->sufiksy = malloc(DLUGSLOWA*i*sizeof(char));
    p->liczba_wyst = p->rozmiar = i;
    i = 0;
    fgetc(fp);
    while ((k = fgetc(fp)) != '\n' && k != EOF){
        p->sufiksy[i] = k;
        i++;
    }
    p->sufiksy[i] = '\0';
    p->nast = NULL;
    return 0;
}

struct s* czytaj_tekst_do_bazy (char* plik, int rzad)
{
    FILE* fp = fopen(plik, "r");
    if(fp == NULL)
    {
        printf("Nie znaleziono pliku z tekstem.\n");
        return NULL;
    }
    struct s* skorowidz;
    struct s* p;
    fpos_t pozycja;
    int i = 0;
    char sufiks[1000] = "";
    char prefiks[1000] = "";
    while (i < rzad-1)
    {
        if(fscanf(fp, "%s", sufiks) != 1){
            printf("Podano za krotki tekst.\n");
            return NULL;
        };
        strcat(prefiks, sufiks);
        if (i == 0)
            fgetpos(fp, &pozycja);
        if (i<rzad-2)
            strcat(prefiks, " ");
        i++;
    };
    fscanf(fp, "%s", sufiks);
    i = 0;
    skorowidz = stworz_skorowidz(prefiks, sufiks);
    strcpy(prefiks, "");
    strcpy(sufiks, "");
    fsetpos(fp, &pozycja);
    while (fscanf(fp, "%s", sufiks) == 1)
    {
        if (strlen(sufiks) > DLUGSLOWA){
            printf ("W programie zadano za krotka dlugosc slowa, prosze ja zmienic\n");
            return 0;
        }
        strcat(prefiks, sufiks);
        if (i == 0)
            fgetpos(fp, &pozycja);
        if (i<rzad-2)
            strcat(prefiks, " ");
        if(i == rzad-2)
        {
            if (fscanf(fp, "%s", sufiks) == 1)
            {
                if ((p = znajdz_haslo(skorowidz, prefiks))!= NULL)
                    dodaj_wystapienie(p, sufiks);
                else
                    dodaj_haslo(skorowidz, prefiks, sufiks);
                fsetpos(fp, &pozycja);
                i = -1;
                strcpy(prefiks, "");
                strcpy(sufiks, "");
            }
        }
        i++;
        //wypisz_skorowidz(stdout, skorowidz);
    }

    return skorowidz;
}
