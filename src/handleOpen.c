#include <stdio.h>
#include "handler.h"

int fileOpened = 0;

int handleOpen(char* fileName) {
	FILE* fptr;

	//read file
	fptr = fopen(fileName, "r");
	//if no file, create file
	if (fptr == NULL) {
		fptr = fopen(fileName, "w");
		if (fptr == NULL) {
			printf("CMS: The file is not opened.\n");
			return;
		}
		else {
			//to write into file stream
			fprintf(fptr, "ID|Name|Programme|Mark\n");
			fclose(fptr);
			printf("CMS: The file \"%s\" created successfully.\n", fileName);
		}
	}
	else {
		fclose(fptr);
	}

	printf("CMS: The database file \"%s\" is successfully opened.", fileName);
	fileOpened = 1;
	return;
}
