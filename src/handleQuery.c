#include <stdio.h>
#include "handler.h"

int handleQuery(char* cmdLine, char* fileName) {
	//check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	// check format for QUERY
	int searchID;
	if (sscanf(cmdLine, "QUERY ID=%d", &searchID) != 1) {
		printf("CMS: Invalid format. Format: QUERY ID=<id>\n");
		return;
	}
	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("CMS: Error - Could not open file %s\n", fileName);
		return;
	}

	char line[512];

	// get the records, skipping the header row
	fgets(line, sizeof(line), fptr);
	int id;
	char name[100];
	char programme[100];
	float mark;
	int found = 0;

	while (fscanf(fptr, "%d|%[^|]|%[^|]|%f",
		&id,
		name,
		programme,
		&mark) == 4) {

		if (id == searchID) {

			printf("CMS: The record with ID=%d is found in the data table.\n", searchID);

			printf("%-10s | %-15s | %-15s | %-5s\n",
				"ID", "Name", "Programme", "Mark");

			printf("%-10d | %-15s | %-15s | %-5.1f\n",
				id,
				name,
				programme,
				mark);

			found = 1;
			break;
		}
	}

	if (!found) {
		printf("CMS: The record with ID=%d does not exist.\n", searchID);
	}

	fclose(fptr);
}