#include <stdio.h>
#include <string.h>
#include "handler.h"

int handleUpdate(char* cmdLine, char* fileName, char* userName) {
	// check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	// check format for UPDATE
	int searchID;
	if (sscanf(cmdLine, "UPDATE ID=%d", &searchID) != 1) {
		printf("CMS: Invalid format. Format: UPDATE ID=<id>\n");
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
	int updateIndex = -1;

	// get the records, skipping the header row
	fgets(line, sizeof(line), fptr);
	int id;
	char name[100];
	char programme[100];
	float mark;
	int found = 0;
	char markStr[20] = "";

	while (fscanf(fptr, "%d|%[^|]|%[^|]|%f",
		&id,
		name,
		programme,
		&mark) == 4) {

		if (id == searchID) {
			found = 1;
			char* namePosition = strstr(cmdLine, "Name=");
			char* progPosition = strstr(cmdLine, "Programme=");
			char* markPosition = strstr(cmdLine, "Mark=");

			//if name is null, remains the same
			if (namePosition != NULL) {
				//ignore the 'Name='
				namePosition += 5; // [ Name=sj Programme=cyber Mark=23.2 ] -> [ sj Programme=cyber Mark=23.2 ]
				char* nameEnd = progPosition;

				if (nameEnd == NULL) nameEnd = markPosition;
				if (nameEnd == NULL) {
					strcpy(name, namePosition);
				}
				else {
					//from nameposition to end of name remove, result is the name target
					int nameTarget = nameEnd - namePosition - 1; //left with 'sj ' -1 becomes 'sj'

					//name is destination, namePosition is source, and nameTarget is the length
					//so nameTarget is 2, means from namePosition take 0 1 index, taking 'sj'
					strncpy(name, namePosition, nameTarget); //strncpy copies specifics, strcpy copies entire
					name[nameTarget] = '\0';
				}

				if (strlen(name) == 0) {
					while (1) {
						printf("%s: Enter Name: ", userName);
						fgets(name, sizeof(name), stdin);
						name[strcspn(name, "\n")] = 0;
						if (strlen(name) > 0) break;
					}
				}

			}
			//if programme is null, remains the same
			if (progPosition != NULL) {
				//skip Programme=
				progPosition += 10;
				char* progEnd = markPosition;
				if (progEnd == NULL) {
					strcpy(programme, progPosition);
				}
				else {
					//end of programme - programme position gives the length of the target -1, to remove space.
					int progTarget = progEnd - progPosition - 1;
					strncpy(programme, progPosition, progTarget);
					programme[progTarget] = '\0';
				}
				if (strlen(programme) == 0) {
					while (1) {
						printf("%s: Enter Programme: ", userName);
						fgets(programme, sizeof(programme), stdin);
						programme[strcspn(programme, "\n")] = 0;
						if (strlen(programme) > 0) break;
					}
				}
			}

			//if mark is null, remains the same
			if (markPosition == NULL) {
				mark = mark;
			}
			else {
				//skip Mark=
				markPosition += 5;
				//check if its numeric
				if (strlen(markPosition) == 0) {
					while (1) {
						printf("%s: Enter Marks: ", userName);
						fgets(markStr, sizeof(markStr), stdin);
						markStr[strcspn(markStr, "\n")] = 0;
						if (sscanf(markStr, "%f", &mark) != 1) {
							printf("CMS: Error - Mark must be a number.\n");
						}
						//check if 0-100
						else if (mark < 0.0 || mark > 100.0) {
							printf("CMS: Error - Mark must be between 0 and 100.\n");
						}
						else break;
					}
				}
				else {
					if (sscanf(markPosition, "%f", &mark) != 1) {
						printf("CMS: Error - Mark must be a number.\n");
						return;
					}
					else if (mark < 0.0 || mark > 100.0) {
						printf("CMS: Error - Mark must be between 0 and 100.\n");
						return;
					}
				}
			}
			break;
		}
	}
	fclose(fptr);

	if (!found) {
		printf("CMS: The record with ID=%d does not exist.\n", searchID);
		return;
	}

	FILE* fptr2 = fopen(fileName, "r");
	// read header into allLines
	fgets(allLines[lineCount], sizeof(allLines[lineCount]), fptr2);
	lineCount++;

	// read remaining lines, storing each one
	while (fgets(line, sizeof(line), fptr2)) {
		int existingID;
		sscanf(line, "%d|", &existingID);
		if (existingID == searchID) {
			found = 1;
			updateIndex = lineCount; // remember which line to skip later
		}
		strcpy(allLines[lineCount], line);
		lineCount++;
	}
	fclose(fptr2);

	//rewrite all lines, only changing updated record
	FILE* fptr3 = fopen(fileName, "w");
	if (!fptr3) {
		printf("CMS: Error - Could not open file %s for writing\n", fileName);
		return;
	}
	for (int i = 0; i < lineCount; i++) {
		if (i == updateIndex) {
			fprintf(fptr3, "%d|%s|%s|%.1f\n", id, name, programme, mark);
		}
		else {
			fprintf(fptr3, "%s", allLines[i]);
		}
	}
	fclose(fptr3);

	printf("CMS: The record with ID=%d is successfully updated.\n", searchID);

}