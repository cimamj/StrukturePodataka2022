#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024
#define EXIT_NOT_OPENING_FILE -1

typedef struct _student {
	char Name[MAX_SIZE];
	char Surname[MAX_SIZE];
	double points;
} Student;

int ReadLines(char* FileName);
Student* AllocateForArrayOfStructures(int NumberOfStudents, char* FileName);
double MaxPoints(int NumberOfStudents, Student* Students);

int main() {
	int i = 0;
	int NumberOfStudents = 0;
	Student* students = NULL;
	NumberOfStudents = ReadLines("PopisStudenata.txt");
	students = AllocateForArrayOfStructures(NumberOfStudents, "PopisStudenata.txt");

	for (i = 0; i < NumberOfStudents; i++) {
		printf("Details for %d. student:\n", i + 1);
		printf("Name: %s\n", students[i].Name);
		printf("Surname: %s\n", students[i].Surname);
		printf("Apsolute points: %lf\n", students[i].points);
		printf("Relative points: %lf\n", (students[i].points / MaxPoints(NumberOfStudents, students) * (double)100));
		printf("\n");
	}

	return EXIT_SUCCESS;

}

int ReadLines(char* FileName) {
	int counter = 0;
	FILE* file = NULL;
	char buffer[MAX_LINE] = { 0 };

	file = fopen(FileName, "r");
	if (!file) {
		printf("Error!");
		return EXIT_NOT_OPENING_FILE;
	}

	while (!feof(file)) {
		fgets(buffer, MAX_LINE, file);
		counter++;
	}

	fclose(file);
	return counter;
}


Student* AllocateForArrayOfStructures(int NumberOfStudents, char* FileName) {
	FILE* file = NULL;
	Student* student = NULL;
	int counter = 0;

	student = (Student*)malloc(NumberOfStudents * sizeof(Student));
	file = fopen(FileName, "r");
	if (!file) {
		printf("Error!");
		free(student);
		return EXIT_NOT_OPENING_FILE;
	}

	while (!feof(file)) {
		fscanf(file, " %s %s %lf", (student+counter)->Name, (student+counter)->Surname, &((student+counter)->points));
		counter++;
	}

	fclose(file);
	return student;
}


double MaxPoints(int NumberOfStudents, Student* Students) {
	double max = 0.0;
	int i = 0;

	max = Students[0].points;

	for (i = 1; i < NumberOfStudents; i++) {
		if (Students[i].points > max) {
			max = Students[i].points;
		}
	}

	return max;
}