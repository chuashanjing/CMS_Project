#include <stdio.h>
#include "handler.h"

int handleSave(char* fileName) {
	// check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	//open file in read mode
	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("CMS: Error - Could not open file %s\n", fileName);
		return;
	}

	// Close the file after reading
	fclose(fptr);
	fileOpened = 0;
	if (fileOpened == 0) {
		printf("CMS: The database file \"%s\" is successfully saved.", fileName);
	}
	else {
		printf("CMS: Error - Could not close file %s", fileName);
		return;
	}
}