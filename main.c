#include <time.h>
#include "baza.h"
#include "ngram.h"
#include "plik.h"
#include "stats.h"

void wyswietl_info ();
void wyswietl_blad ();

int main(int argc, char** argv)
{
    srand(time(NULL));
    int rzad, ilosc_slow, ilosc_akapitow;
    char plik_baza[DLUGSLOWA];
    char plik_wyjscie[DLUGSLOWA];
    char plik_tekst [DLUGSLOWA];

    if (argc == 12)
    {
        if (strcmp(argv[1], "-bgen") == 0)
        {
            if (strcmp(argv[2], "-s") == 0)
                ilosc_slow = atoi(argv[3]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[4], "-a") == 0)
                ilosc_akapitow = atoi(argv[5]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[6], "-n") == 0)
                rzad = atoi (argv[7]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[8], "-b") == 0)
                strcpy(plik_baza, argv[9]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[10], "-w") == 0)
                strcpy(plik_wyjscie, argv[11]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}

            struct s* skorowidz = wczytaj_baze_z_pliku(plik_baza, rzad);
            if (skorowidz == NULL){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
            if (napisz_tekst(plik_wyjscie, skorowidz, rzad, ilosc_slow, ilosc_akapitow) == 0){
                wyswietl_blad(); wyswietl_info(); return 0;
            }
        }
    }

    else if (argc == 14)
    {
        if (strcmp(argv[1], "-all") == 0)
        {
            if (strcmp(argv[2], "-s") == 0)
                ilosc_slow = atoi(argv[3]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[4], "-a") == 0)
                ilosc_akapitow = atoi(argv[5]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[6], "-n") == 0)
                rzad = atoi (argv[7]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[8], "-b") == 0)
                strcpy(plik_baza, argv[9]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[10], "-w") == 0)
                strcpy(plik_wyjscie, argv[11]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[12], "-p") == 0)
                strcpy(plik_tekst, argv[13]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}

            struct s* skorowidz = czytaj_tekst_do_bazy(plik_tekst, rzad);
            if (skorowidz == NULL){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
            if(zapisz_baze_do_pliku(plik_baza, skorowidz) == 0){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
            if(napisz_tekst(plik_wyjscie, skorowidz, rzad, ilosc_slow, ilosc_akapitow) == 0){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
        }
    }

    else if (argc == 8 || argc == 6)
    {
        if (strcmp(argv[1], "-baza") == 0)
        {
            if (strcmp(argv[2], "-n") == 0)
                rzad = atoi (argv[3]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[4], "-b") == 0)
                strcpy(plik_baza, argv[5]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[6], "-p") == 0)
                strcpy(plik_tekst, argv[7]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}

            struct s* skorowidz = czytaj_tekst_do_bazy(plik_tekst, rzad);
            if(skorowidz == NULL){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
            if(zapisz_baze_do_pliku(plik_baza, skorowidz) == 0){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
        }
        if (strcmp(argv[1], "-stats") == 0)
        {
            if (strcmp(argv[2], "-n") == 0)
                rzad = atoi(argv[3]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}
            if (strcmp(argv[4], "-b") == 0)
                strcpy(plik_baza, argv[5]);
            else { wyswietl_blad(); wyswietl_info(); return 0;}

            if (statystyki_calosc (plik_baza, rzad) == 0){
                wyswietl_blad(); wyswietl_info(); return 0;
            };
            if (argc == 8)
            {
                if (strcmp(argv[6], "-p") == 0)
                    statystyki_ngramu(plik_baza, rzad, argv[7]);
                else { wyswietl_blad(); wyswietl_info(); return 0;}
            }

        }
    }
    else
    {
        wyswietl_blad();
        wyswietl_info();
    }
    return 0;
}

void wyswietl_info()
{
    printf ("Generacja bazy danych: ./ggen -baza -n rzad -b baza -p plik\n");
    printf ("Generacja tekstu z bazy danych: ./ggen -bgen -s slowa -a akapity -n rzad -b baza -w wyjscie\n");
    printf ("Generacja bazy i tekstu: ./ggen -all -s slowa -a akapity -n rzad -b baza -w wyjscie -p plik\n");
    printf ("Generacja statystyki tekstu: ./ggen -stats -n rzad -b baza\n");
    printf ("Generacja statystyki tekstu i ngramu: ./ggen -stats -n rzad -b baza -p prefiks\n\n");

    printf ("baza- plik bazy danych, slowa- ilosc slow, akapity- ilosc akapitow, rzad- rzad ngramow, wyjscie- nazwa pliku do");
    printf (" ktorego bedzie zapisywany tekst, plik- nazwa pliku zawierajacego tekst do analizy, prefiks- prefiks ngramu\n\n");
    printf ("Podane plik powinny sie znajdowac w katalogu z plikiem wykonywanym programu i powinny zostac utworzone przed wywolaniem programu (puste)\n");

}

void wyswietl_blad (){
        printf ("Niepoprawne wywolanie programu.\nInstrukcja wywolania:\n\n");
}
