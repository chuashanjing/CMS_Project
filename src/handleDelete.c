#include <stdio.h>
#include <string.h>
#include "handler.h"

int handleDelete(char* cmdLine, char* fileName, char* userName) {
	// check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	// check format for DELETE
	int searchID;
	if (sscanf(cmdLine, "DELETE ID=%d", &searchID) != 1) {
		printf("CMS: Invalid format. Format: DELETE ID=<id>\n");
		return;
	}

	FILE* fptr = fopen(fileName, "r");
	if (!fptr) {
		printf("CMS: Error - Could not open file %s\n", fileName);
		return;
	}

	char line[512];
	char allLines[1000][512];
	int lineCount = 0;
	int found = 0;
	int deleteIndex = -1;

	// read header into allLines
	fgets(allLines[lineCount], sizeof(allLines[lineCount]), fptr);
	lineCount++;

	// read remaining lines, storing each one
	while (fgets(line, sizeof(line), fptr)) {
		int existingID;
		sscanf(line, "%d|", &existingID);
		if (existingID == searchID) {
			found = 1;
			deleteIndex = lineCount; // remember which line to skip later
		}
		strcpy(allLines[lineCount], line);
		lineCount++;
	}
	fclose(fptr);

	// if not found, print warning
	if (!found) {
		printf("CMS: The record with ID=%d does not exist.", searchID);
		return;
	}

	// reparse and print the matched line for display
	int id;
	char name[100], programme[100];
	float mark;
	sscanf(allLines[deleteIndex], "%d|%[^|]|%[^|]|%f", &id, name, programme, &mark);

	// double confirm deletion
	char confirm[10];
	printf("CMS: Are you sure you want to delete record with ID=%d? Type 'Y' to Confirm or type 'N' to cancel.\n", id);
	printf("%s: ", userName);
	fgets(confirm, sizeof(confirm), stdin);
	confirm[strcspn(confirm, "\n")] = 0;

	if (strcmp(confirm, "Y") != 0) {
		printf("CMS: Deletion cancelled. No changes were made.");
		return;
	}

	// write all lines back except the deleted one
	FILE* fptr2 = fopen(fileName, "w");
	if (!fptr2) {
		printf("CMS: Error - Could not open file %s for writing\n", fileName);
		return;
	}
	for (int i = 0; i < lineCount; i++) {
		if (i != deleteIndex) {
			fprintf(fptr2, "%s", allLines[i]);
		}
	}
	fclose(fptr2);

	printf("CMS: The record with ID=%d is successfully deleted.", searchID);
}