#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 512

typedef struct _polinom {

	int koeficijent;
	int eksponent;
	struct _polinom* next;

}Polinom;

int ucitajIzDatoteke(Polinom* HEAD1, Polinom* HEAD2, char* imeDatoteke);
int citajIzDatoteke(Polinom* HEAD, char* imeDatoteke);
int Sortiraj(Polinom* HEAD, int koeficijent, int eksponent);
Polinom* pronadiPrethodnog(Polinom* HEAD, Polinom* P);
int zbrojiPolinome(Polinom* HEAD1, Polinom* HEAD2, Polinom* Suma);
int pomnoziPolinome(Polinom* HEAD1, Polinom* HEAD2, Polinom* Produkt);
int ispis(Polinom* HEAD);

int main() {

	Polinom* HEAD1 = (Polinom*) malloc(sizeof(Polinom));
	Polinom* HEAD2 = (Polinom*)malloc(sizeof(Polinom));

	Polinom* Suma = (Polinom*)malloc(sizeof(Polinom));
	Polinom* Produkt = (Polinom*)malloc(sizeof(Polinom));

	if (!HEAD1)
		return -1;
	if (!HEAD2)
		return -1;
	if (!Suma)
		return -1;
	if (!Produkt)
		return -1;

	HEAD1->next = NULL;
	HEAD2->next = NULL;
	Suma->next = NULL;
	Produkt->next = NULL;

	char* imeDatoteke = "Polinom.txt";

	ucitajIzDatoteke(HEAD1, HEAD2, imeDatoteke);
	zbrojiPolinome(HEAD1, HEAD2, Suma);
	pomnoziPolinome(HEAD1, HEAD2, Produkt);
	printf("Suma polinoma je \n");
	ispis(Suma);
	printf("\nProdukt polinoma je \n");
	ispis(Produkt);


	return 0;
}


int ucitajIzDatoteke(Polinom* HEAD1, Polinom* HEAD2,char* imeDatoteke) {

	FILE* fp = NULL;
	char BUFFER[MAX] = { 0 };

	fp = fopen(imeDatoteke, "r");

	if (!fp)
		return -1;

	fgets(BUFFER, MAX, fp);
	citajIzDatoteke(HEAD1, BUFFER);
	//kako mozemo koristit isti buffer, al nebi tribalo citat onda od proslog ??
	fgets(BUFFER, MAX, fp);
	citajIzDatoteke(HEAD2, BUFFER);


	return 0;
}

int citajIzDatoteke(Polinom* HEAD, char* BUFFER) {

	int n = 0;
	int koeficijent = 0;
	int eksponent = 0;
	char* tempBUFFER = BUFFER;
	//proba i samo sa BUFFER (sam po sebi pokazivac) i radi, cemu tempBUFFER ??
	while (strlen(tempBUFFER) > 1) { //strlen broj znakova plus 1 (%n na kraju), zato >1
		//pretp da se ode tempBUFFER gleda ka *
		sscanf(tempBUFFER, "%d %d %n", &koeficijent, &eksponent, &n);
		tempBUFFER += n; //ode ka adresa ??

		//printf("%d %d %d \n", koeficijent, eksponent, n);
		//printf("%d\n", strlen(tempBUFFER));

		Sortiraj(HEAD, koeficijent, eksponent);
	}

	return 0;
}

int Sortiraj(Polinom* HEAD, int koeficijent, int eksponent) {

	Polinom* P = HEAD;
	
	//prvo od ovog, zamisli da lista vec postoji i usporedujes sa eksp koji je van liste kojeg tek triba dodat
	while (P->next != NULL && P->next->eksponent >= eksponent) { // p razl od null da prode cilu listu, ali ?? sta se desi kod prvog P je NULL pa sta je onda P->next pitaj sentu, proba pokrenit sa P != NULL i puka program ocito triba P->next != NULL
		P = P->next;
	}
	
	if (P->next != NULL && P->next->eksponent == eksponent) {
		P->next->koeficijent += koeficijent;
	}

	else {
		Polinom* novi = malloc(sizeof(Polinom));

		if (!novi) {
			return -1;
		}

		novi->next = P->next;
		P->next = novi;
		//kako ispisuje od veceg prema manjem wtf
		novi->koeficijent = koeficijent;
		novi->eksponent = eksponent;

	}



	//Prethodni = pronadiPrethodnog(HEAD, P); ipak ne triba jer P je prethodni,a ja san P razumia da je taj na kome je pokaz
	//Prethodni->next = novi;
	//novi->next = P;

	return 0;
}

Polinom* pronadiPrethodnog(Polinom* HEAD, Polinom* P) {

	Polinom* H = HEAD;

	while (H != NULL && H->next != P) {
		H = H->next;
	}
	 
	//ne triba ova fja

	return H;
}

int zbrojiPolinome(Polinom* HEAD1, Polinom* HEAD2, Polinom* Suma) {

	//slat opet u sort i napravit jednu veliku vezanu listu njih svih

	Polinom* P1 = HEAD1->next;
	Polinom* P2 = HEAD2->next;

	while (P1 != NULL) {
		Sortiraj(Suma, P1->koeficijent, P1->eksponent);
		P1 = P1->next;
	}

	while (P2 != NULL) {
		Sortiraj(Suma, P2->koeficijent, P2->eksponent);
		P2 = P2->next;
	}

	return 0;
}

int pomnoziPolinome(Polinom* HEAD1, Polinom* HEAD2, Polinom* Produkt) {

	Polinom* P1 = HEAD1->next;
	Polinom* P2 = HEAD2->next;
	//u notepadu skuzia prvi prvog pol sa svima drugog pol
	while (P1 != NULL) {
		P2 = HEAD2->next; //zasto bez ovof kriv produkt bude
		while (P2 != NULL) {
			Sortiraj(Produkt, (P1->koeficijent) * (P2->koeficijent), (P1->eksponent) + (P2->eksponent));
			P2 = P2->next;
		}
		P1 = P1->next;
	}

	return 0;
}

int ispis(Polinom* HEAD) {

	Polinom* P = HEAD->next;

	while (P != NULL) {
		printf("%dx^%d", P->koeficijent, P->eksponent);
		if (P->next != NULL)
			printf(" + ");
		P = P->next;
	}

	return 0;
}
