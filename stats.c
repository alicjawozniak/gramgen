#include "stats.h"
#include "baza.h"

void statystyki_calosc(char* plik, int rzad){
    char najczestsze[DLUGSLOWA];
    char najrzadsze[DLUGSLOWA];
    int ilosc_ngramow = 0;
    int wyst_min= 1;
    int wyst_max = 1;

    char k;
    char temp [DLUGSLOWA] = "";
    char prefiks [10*DLUGSLOWA] = "";
    int temp_wyst = 0;
    int i = 0;

    FILE* fp = fopen (plik, "r");

    while (fscanf(fp, "%s", temp) == 1){
            while (i < rzad - 1){
                strcat(prefiks, temp);
                if (i < rzad - 2)
                    strcat (prefiks, " ");
                i++;
                if (i != rzad - 1)
                    fscanf (fp, "%s", temp);
            }
            fscanf (fp, "%d", &temp_wyst);
            if (temp_wyst < wyst_min){
                strcpy (najrzadsze, prefiks);
                wyst_min = temp_wyst;
            }
            if (temp_wyst > wyst_max){
                strcpy (najczestsze, prefiks);
                wyst_max = temp_wyst;
            }
            while ((k = fgetc (fp)) != '\n' && k != EOF)
                ;
            strcpy (prefiks, "");
            i = 0;
            ilosc_ngramow++;
    }
    printf ("W bazie jest zawarte: %d n-gramow\nZ czego najczesciej wystepuje: \"%s\" (%d razy)\na najrzadziej: \"%s\" (%d razy)\n",
            ilosc_ngramow, najczestsze, wyst_max, najrzadsze, wyst_min);

}

void statystyki_ngramu(char* plik, int rzad, char* ngram){
    char temp [DLUGSLOWA] = "";
    char prefiks [10*DLUGSLOWA] = "";
    int i = 0, j = 0;
    FILE* fp = fopen (plik, "r");
    int ilosc_ngramow = 0;
    int ilosc_wyst = 1;
    int max_wyst = 0;
    char max_sufiks [DLUGSLOWA] = "";
    char temp_sufiks[DLUGSLOWA] = "";
    int temp_wyst;
    char k;
    fpos_t pozycja;

    while (fscanf(fp, "%s", temp) == 1){
            while (i < rzad - 1){
                strcat(prefiks, temp);
                if (i < rzad - 2)
                    strcat (prefiks, " ");
                i++;
                if (i != rzad - 1)
                    fscanf (fp, "%s", temp);
            }
            if (strcmp(ngram, prefiks) == 0)
                break;
            while ((k = fgetc (fp)) != '\n' && k != EOF)
                ;
            strcpy (prefiks, "");
            i = 0;
            ilosc_ngramow++;
    }
    fscanf (fp, "%d", &temp_wyst);
    fscanf(fp, "%s", temp_sufiks);
    fgetpos (fp, &pozycja);
    while (i < temp_wyst){
        fsetpos (fp, &pozycja);
        while (fscanf(fp, "%s", temp) == 1 && j <= temp_wyst - i){
            if (strcmp(temp_sufiks, temp) == 0)
                ilosc_wyst++;
            j++;
        }
        j = 0;
        i++;
        if (ilosc_wyst > max_wyst){
            strcpy (max_sufiks, temp_sufiks);
            max_wyst = ilosc_wyst;
        }
        fsetpos (fp, &pozycja);
        fscanf(fp, "%s", temp_sufiks);
        fgetpos (fp, &pozycja);
        ilosc_wyst = 1;
    }
    printf ("Ngram z prefiksem \"%s\" wystepuje w tekscie %d razy. ",
             ngram, temp_wyst);
    printf ("Najbardziej prawdopodobnym sufiksem dla niego jest \"%s\", jego prawdopodobienstwo wynosi %d\%%\n",
            max_sufiks, (int)(100*max_wyst/temp_wyst));
}
