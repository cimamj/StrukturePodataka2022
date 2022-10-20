#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024


typedef struct student {

    char ime[MAX_LINE];
    char prezime[MAX_LINE];
    double bodovi;

}Student;

int procitajBrStud(char* imeDat);
Student* alocirajIucitaj(char* imeDat, int brojStud);
void ispis(Student* studenti, int brojStud);

int main()
{
    char* imeDat = NULL;
    int brojStud = 0;
    Student* studenti = NULL;

    imeDat = "studenti.txt";

    brojStud = procitajBrStud(imeDat);

    studenti = alocirajIucitaj(imeDat, brojStud);

    ispis(studenti, brojStud);

    return 0;
}


int procitajBrStud(char* imeDat)
{
    int brojac = 0;
    FILE* datoteka = NULL;
    char BUFFER[MAX_LINE] = { 0 };

    datoteka = fopen(imeDat, "r");

    if (!datoteka)
    {
        printf("Datoteka je neuspjesno ucitana\n");
        return -1;
    }

    while (!feof(datoteka))
    {
        fgets(BUFFER, MAX_LINE, datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}

Student* alocirajIucitaj(char* imeDat, int brojStud)
{
    Student* studenti = NULL;
    FILE* datoteka = NULL;
    int brojac = 0;

    datoteka = fopen(imeDat, "r");

    if (!datoteka)
    {
        printf("Datoteka je neuspjesno ucitana\n");
        return NULL;
    }

    studenti = (Student*)malloc(brojStud * sizeof(Student));

    if (!studenti)
    {
        printf("Neuspjesna alokacija studenata");
        return NULL;
    }

    while (!feof(datoteka))
    {
        fscanf(datoteka, "%s %s %d", (studenti + brojac)->ime, (studenti + brojac)->prezime, &((studenti + brojac)->bodovi));
        brojac++;
    }

    fclose(datoteka);
    return studenti;
}

void ispis(Student* studenti, int brojStud)
{
    //relativni broj bodova (u odnosu na najveci br bod koji je 100%)

    double max = 0;
    max = studenti->bodovi;  
    int i = 0;
    printf("\n%lf\n", max);

    for (i = 0;i < brojStud;i++) {
        if ((studenti + i)->bodovi > max)
            max = (studenti + i)->bodovi;
    }


   
    //int bodovi = studenti->bodovi;
    //float relativni = (float)bodovi / max * 100;
    //printf("%f\n", relativni);   // sta se desava ode

    for (i = 0;i < brojStud;i++) {
        printf("%s %s %d %f\n", (studenti + i)->ime, (studenti + i)->prezime, (studenti + i)->bodovi, ((float)((studenti + i)->bodovi)/max *100));
    }
}


