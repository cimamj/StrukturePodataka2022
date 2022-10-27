#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 128
#define ERROR_FAIL_TO_ALLOCATE -1

struct _student;
typedef struct _student* Position;
typedef struct _student {
	char Name[MAX_SIZE];
	char Surname[MAX_SIZE];
	int age;
	Position next;
}Student;

int PrependList(Position p, char* ime, char* prezime, int godiste);
int PrintList(Position p);
int AppendList(Position p, char* ime, char* prezime, int godiste);
Position FindPerson(char* prezime, Position p);
Position FindPrevious(char* prezime, Position p);
int DeletePerson(char* prezime, Position p);

int main(int argc, char** argv)
{
	Student head = { .Name = {0}, .Surname = {0}, .age = 0, .next = NULL };
	Position p = &head;
	char z;
	Student temp = { .Name = {0}, .Surname = {0}, .age = 0, .next = NULL };
	Position t = &temp;
	Position trazeni;
	Position prethodni;

	while (1) {
		printf("MENU:\nChoose:\nP - prepend list\nK - append list\n"
			"I - print list\nT - find person\nR - find previous person\n"
			"O - delete person from the list\nE - exit\n\n");
		scanf(" %c", &z);
		switch (toupper(z))
		{
		case 'P':
			printf("Unesite podatke osobe");
			printf("\nIme: ");
			scanf(" %s", temp.Name);
			printf("Prezime: ");
			scanf(" %s", temp.Surname);
			printf("Godiste: ");
			scanf("%d", &temp.age);
			PrependList(p, t->Name, t->Surname, t->age);
			printf("\nOsoba je dodana na pocetak liste!\n\n");
			break;

		case 'K':
			printf("Unesite podatke osobe");
			printf("\nIme: ");
			scanf(" %s", temp.Name);
			printf("Prezime: ");
			scanf(" %s", temp.Surname);
			printf("Godiste: ");
			scanf("%d", &temp.age);
			AppendList(p, t->Name, t->Surname, t->age);
			printf("\nOsoba je dodana na kraj liste!\n\n");
			break;

		case 'I':
			printf("LISTA:\n");
			PrintList(p->next);
			puts("\n");
			break;

		case 'T':
			printf("Unesite prezime osobe koju trazite: ");
			scanf(" %s", temp.Surname);
			trazeni = FindPerson(t->Surname, p->next);
			printf("\nTrazena osoba:\nIme: %s\nPrezime: %s\nGodiste: %d\n\n"
				, trazeni->Name, trazeni->Surname, trazeni->age);
			break;

		case 'R':
			printf("Unesite prezime osobe od koje trazite prethodnu: ");
			scanf(" %s", temp.Surname);
			prethodni = FindPrevious(t->Surname, p->next);
			if (prethodni != NULL)
				printf("\nPrethodna osoba u listi:\nIme: %s\nPrezime: %s\nGodiste: %d\n\n"
					, prethodni->Name, prethodni->Surname, prethodni->age);
			break;

		case 'O':
			printf("Unesite prezime osobe koju zelite izbrisati iz liste: ");
			scanf(" %s", temp.Surname);
			DeletePerson(t->Surname, p);
			printf("\nOsoba je izbrisana iz liste!\n\n");
			break;

		case 'E':
			puts("\nIzlaz iz programa!\n");
			return 1;
			break;

		default:
			printf("\nGreska pri unosu!\nPokusajte ponovno!\n");
			break;
		}
	}


	return EXIT_SUCCESS;
}

int PrependList(Position p, char* name, char* surname, int age)
{
	Position NewPerson = NULL;
	NewPerson = (Position)malloc(sizeof(Student));
	if (!NewPerson)
		return -1;
	strcpy(NewPerson->Name, name);
	strcpy(NewPerson->Surname, surname);
	NewPerson->age = age;
	NewPerson->next = p->next;
	p->next = NewPerson;
	return EXIT_SUCCESS;
}

int PrintList(Position p)
{
	Position temp = p->next;
	while (temp) {
		printf("Name: %s\nSurname: %s\nAge: %d\n\n", temp->Name, temp->Surname, temp->age);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int AppendList(Position p, char* name, char* surname, int age)
{
	Position NewPerson = NULL;
	Position temp = p;
	NewPerson = (Position)malloc(sizeof(Student));
	if (!NewPerson)
		return -1;
	strcpy(NewPerson->Name, name);
	strcpy(NewPerson->Surname, surname);
	NewPerson->age = age;
	while (temp->next)
		temp = temp->next;
	NewPerson->next = temp->next;
	temp->next = NewPerson;
	return EXIT_SUCCESS;
}

Position FindPerson(Position p, char* surname)
{
	Position temp = p;
	while (temp) {
		if (!strcmp(surname, temp->Surname))
			return temp;
		temp = temp->next;
	}
	printf("Student is not on the list!\n");
	return NULL;
}

Position FindPrevious(Position p, char* surname)
{
	Position temp = p;
	while (temp->next != NULL && !strcmp(surname, temp->next->Surname)) {
		temp = temp->next;
	}
	if (temp->next == NULL){
		printf("Student is not on the list\n");
		return NULL;
	}
	return temp;
}

int DeletePerson(Position p, char* surname)
{
	Position temp = p;
	Position prev = FindPrevious(temp, surname);
	if (prev != NULL) {
		temp = prev->next;
		prev->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}