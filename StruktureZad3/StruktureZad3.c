#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 1024

typedef struct _student {
    char Name[STRMAX];
    char surname[STRMAX];
    int age;
    struct _student* next;
} Student;

int PreppendList(Student* HEAD, Student* element);
int AppendList(Student* HEAD, Student* element);
int PrintList(Student* HEAD);
int menu(Student* HEAD);
Student* FindPerson(Student* HEAD, char* surname);
int DeletePerson(Student* HEAD, Student* element);
int AddAfter(Student* element, Student* noviElement);
int AddBefore(Student* HEAD, Student* element);
int AddToFile(Student* HEAD, char* filename);
int AddFromFile(Student* HEAD, char* filename);
int Sort(Student* HEAD);
Student* FindLast(Student* HEAD);
int SwitchPositions(Student* HEAD, Student* prvi, Student* drugi);
Student* FindPrevious(Student* HEAD, Student* element);
Student* DataInput(void);

int main(void)
{
    Student* HEAD;
    int status = 0;
    HEAD = (Student*)malloc(sizeof(Student));
    if (!HEAD)
        return -1;
    HEAD->next = NULL;

    do {
        status = menu(HEAD);
    } while (!status);

    return 0;
}

int menu(Student* HEAD)
{
    int choice = 0;
    char surname[STRMAX] = { 0 };
    Student* element = NULL;
    char fileName[STRMAX] = { 0 };

    printf("Choose option:\n\t");
    printf("1. Preppend list\n\t");
    printf("2. Append list\n\t");
    printf("3. Find Person (by surname)\n\t");
    printf("4. Print list\n\t");
    printf("5. Add after\n\t");
    printf("6. Add before\n\t");
    printf("7. Sort list\n\t");
    printf("8. Add list to file\n\t");
    printf("9. Add list from file\n\t");
    printf("10. Delete Person\n\t");
    printf("0. Close\n\n");

    scanf(" %d", &choice);

    switch (choice)
    {
    case (1):
        PreppendList(HEAD, DataInput());
        break;
    case (2):
        AppendList(HEAD, DataInput());
        break;
    case (3):
        printf("Enter surname: ");
        scanf(" %s", surname);
        element = FindPerson(HEAD, surname);
        printf("%s %s %d", element->Name, element->surname, element->age);
        break;
    case (4):
        PrintList(HEAD);
        break;
    case (5):
        printf("Enter surname: ");
        scanf(" %s", surname);
        element = FindPerson(HEAD, surname);
        AddAfter(element, DataInput());
        break;
    case (6):
        printf("Enter surname: ");
        scanf(" %s", surname);
        element = FindPerson(HEAD, surname);
        AddBefore(HEAD, element);
        break;
    case (7):
        Sort(HEAD);
        PrintList(HEAD);
        break;
    case (8):
        printf("Enter file name: ");
        scanf(" %s", fileName);
        AddToFile(HEAD, fileName);
        break;
    case (9):
        printf("Enter file name: ");
        scanf(" %s", fileName);
        AddFromFile(HEAD, fileName);
        break;
    case (10):
        printf("Enter surname: ");
        scanf(" %s", surname);
        DeletePerson(HEAD, FindPerson(HEAD, surname));
        break;
    case (0):
        return 1;
    }
    return 0;
}

int PreppendList(Student* HEAD, Student* element)
{

    element->next = HEAD->next;
    HEAD->next = element;

    return 0;
}

int PrintList(Student* HEAD)
{
    Student* P = HEAD->next;

    while (P != NULL) {
        printf("Name: %s\nsurname: %s\nage: %d\n\n", P->Name, P->surname, P->age);
        P = P->next;
    }

    return 0;
}

int AppendList(Student* HEAD, Student* element)
{
    Student* P = FindLast(HEAD);

    element->next = NULL;
    P->next = element;

    return 0;
}

Student* FindPerson(Student* HEAD, char* surname)
{
    Student* P = HEAD->next;

    while (P != NULL && strcmp(P->surname, surname)) {
        P = P->next;
    }

    return P;
}

int DeletePerson(Student* HEAD, Student* element)
{
    Student* P = HEAD;

    while (P != NULL && P->next != element) {
        P = P->next;
    }

    if (P == NULL)
        return -1;
    else
    {
        P->next = P->next->next;
        free(element);
    }

    return 0;
}

int AddAfter(Student* element, Student* noviElement)
{
    noviElement->next = element->next;
    element->next = noviElement;

    return 0;
}

int AddBefore(Student* HEAD, Student* element)
{
    Student* P = HEAD;
    Student* newPerson = (Student*)malloc(sizeof(Student));

    while (P != NULL && P->next != element)
        P = P->next;

    if (P == NULL) {
        free(newPerson);
        return -1;
    }

    AddAfter(P, DataInput());

    return 0;
}

int AddToFile(Student* HEAD, char* filename)
{
    Student* P = HEAD->next;
    FILE* fp = NULL;
    fp = fopen(filename, "w");

    if (fp == NULL)
        return -1;

    while (P != NULL) {
        fprintf(fp, "%s %s %d\n", P->Name, P->surname, P->age);
        P = P->next;
    }

    fclose(fp);

    return 0;
}

int AddFromFile(Student* HEAD, char* filename)
{
    FILE* fp;
    int brojStudenata = 0;
    int i = 0;
    Student* P = FindLast(HEAD);
    char buffer[STRMAX] = { 0 };

    fp = fopen(filename, "r");

    if (fp == NULL)
        return -1;

    while (fgets(buffer, STRMAX, fp))
        brojStudenata++;

    rewind(fp);

    for (i = 0; i < brojStudenata; i++) {
        Student* noviElement = (Student*)malloc(sizeof(Student));
        noviElement->next = NULL;
        P->next = noviElement;
        P = P->next;

        fscanf(fp, "%s %s %d", noviElement->Name, noviElement->surname, &(noviElement->age));
    }

    fclose(fp);
    return 0;
}

int SwitchPositions(Student* HEAD, Student* prvi, Student* drugi)
{
    Student* prethodni = FindPrevious(HEAD, prvi);
    Student* temp = drugi->next;

    prethodni->next = drugi;
    drugi->next = prvi;
    prvi->next = temp;

    return 0;
}

Student* FindPrevious(Student* HEAD, Student* element)
{
    Student* P = HEAD;

    while (P != NULL && P->next != element)
        P = P->next;

    return P;
}

Student* FindLast(Student* HEAD)
{
    return FindPrevious(HEAD, NULL);
}

int Sort(Student* HEAD)
{
    Student* L = HEAD->next;
    Student* R = NULL;

    while (HEAD->next != R) {
        while (L->next != R) {
            if (strcmp(L->surname, L->next->surname) > 0) {
                SwitchPositions(HEAD, L, L->next);
            }
            else
                L = L->next;
        }
        R = FindPrevious(HEAD, R);
        L = HEAD->next;
    }

    return 0;
}

Student* DataInput(void)
{
    Student* P = (Student*)malloc(sizeof(Student));

    if (!P)
        return NULL;

    printf("Enter name, surname and age [name surname age]: ");
    scanf("%s %s %d", P->Name, P->surname, &(P->age));

    return P;
}