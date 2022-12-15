#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 112


typedef struct _dir {

	char name[STRMAX];

	struct _dir* sibiling;
	struct _dir* child;

}Dir;

typedef struct _stog {

	Dir* upper;
	struct _stog* next;

}Stog;

int menu(Dir* ROOT, Stog* HEAD);
int makeDir(Dir* Current);
Dir* goCd(Dir* C, Stog* H);
int Push(Dir* C, Stog* H);
Dir* pop(Stog* H);
int dir(Dir* Current);

int main() {

	Dir* ROOT = NULL;
	Stog* HEAD = NULL;
	int status = 0;

	ROOT = (Dir*)malloc(sizeof(Dir));
	HEAD = (Stog*)malloc(sizeof(Stog));

	if (!ROOT)
		return -1;
	if (!HEAD)
		return -1;

	stcrpy(ROOT->name, "C:");
	ROOT->sibiling = NULL;
	ROOT->child = NULL;
	HEAD->next = NULL;

	do {

		status = menu(ROOT, HEAD);

	} while (!status);


	return 0;
}

int menu(Dir* ROOT, Stog* HEAD) {

	int ret = 0;
	char choice[STRMAX] = { 0 };
	Dir* Current = ROOT;

	printf("md\n");
	printf("cd\n");
	printf("cd..\n");
	printf("dir\n");
	printf("kraj\n");
	printf("\nVas Izbor \n\n");
	scanf(" %s", choice);

	if (!strcmp("md", choice)) {
		makeDir(Current);
	}

	else if (!strcmp("cd", choice)) {
		Current = goCd(Current, HEAD);
		return 0;
	}

	else if (!strcmp("cd..", choice)) {
		Current = Pop(HEAD);
		return 0;
	}

	else if (!strcmp("dir", choice)) {
		dir(Current);
	}

	else if (!strcmp("kraj", choice)) {
		return 1;
	}
		

	return 0;
}

int makeDir(Dir* Current) {

	Dir* direktorij = NULL;
	char ime[STRMAX] = NULL;

	printf("Unesite ime direktorija\n");

	scanf("%s", ime);

	direktorij = (Dir*)malloc(sizeof(Dir));
	strcpy(direktorij->name, ime);


	if (Current->child == NULL) {

		Current->child = direktorij;

	}

	else {
		Current = Current->child;

		while (Current->sibiling != NULL && strcmp(Current->sibiling->name, direktorij->name) > 0)
			Current = Current->sibiling;

		Current->sibiling = direktorij;
	}

	direktorij->child = NULL;
	direktorij->sibiling = NULL;


	return 0;
}

int Push(Dir* C, Stog* H) {

	Stog* temp = H;

	while (temp->next != NULL)
		temp = temp->next;

	Stog* new = NULL;

	new = (Stog*)malloc(sizeof(Stog));
	new->upper = C;
	new->next = NULL;

	return 0;
}

Dir* goCd(Dir* C, Stog* H) {

	Push(C, H);

	Dir* temp = C;
	char* ime = NULL;

	printf("Upisite ime direktorija koje trazite\n");

	scanf(" %s", ime);

	if (temp->child == NULL) { //prazan direktorij
		printf("Direktorij je prazan\n");
			return temp;
	}

	else
	{
		while (temp->sibiling != NULL)
		{
			if (!(strcmp(temp->name, ime)))
			{
				return temp;
			}
			temp = temp->sibiling;
		}

		//kako znat jel doslo do NULL, else prazan dir, ako pukne petlja prije if


	}

}

Dir* pop(Stog* H) {

	Stog* temp = H;
	Stog* Ptemp = NULL;
	Dir* directory = NULL;

	while (temp->next->next != NULL)
		temp = temp->next;

	directory = temp->next->upper;
	Ptemp = temp->next;
	temp->next = NULL;
	free(Ptemp);
}


int dir(Dir* Current) {

	Dir* temp = Current;

	if (temp->child == NULL)
	{
		printf("Direktorij je prazan\n");
	}
	else
	{
		temp = temp->child;
		while (temp->sibiling != NULL)
		{
			printf("%s\n", temp->name);
			temp = temp->sibiling;
		}
	}

	return 0;
}