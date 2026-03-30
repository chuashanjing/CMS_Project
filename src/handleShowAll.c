#include <stdio.h>
#include "handler.h"

int handleShowAll(char* fileName) {
	// check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	//open file in read mode
	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("CMS: Error - Could not open file %s.\n", fileName);
		return 0;
	}

	// Initialize variables to store the data read from the file
	int id;
	char name[100], programme[100], file_name[100];
	float mark;
	char line[512];

	// Reads the first line so that the following while loop does not read it.
	(fgets(line, sizeof(line), fptr));
	printf("%-10s | %-15s | %-15s | %-5s\n", "ID", "Name", "Programme", "Mark"); //Prints column headers.

	// Loop throw every row of file, while checking 4 items are read
	while (fscanf(fptr, "%d | %[^|] | %[^|] | %f", &id, name, programme, &mark) == 4) {
		//Prints the data in a formatted way, with specific width for each column.
		printf("%-10d | %-15s | %-15s | %-5.1f\n", id, name, programme, mark);
	}

	//close file
	fclose(fptr);
}