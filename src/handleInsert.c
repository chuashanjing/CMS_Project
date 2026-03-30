#include <stdio.h>
#include <string.h>
#include "handler.h"

int handleInsert(char* cmdLine, char* fileName, char* userName) {
	//check if file open
	if (!fileOpened) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}

	//if user only type INSERT, tell them error and format
	if (strlen(cmdLine) <= 6) {
		printf("CMS: Invalid format. Format: INSERT ID=<id> Name=<name> Programme=<prog> Mark=<mark>.\n");
		return;
	}

	int id;
	char name[100] = "";
	char programme[100] = "";
	float mark;
	char idStr[20] = "";
	char markStr[20] = "";

	//check if ID is a number
	if (sscanf(cmdLine, "INSERT ID=%d", &id) != 1) {
		printf("CMS: Make sure ID does not contain any alphabets. Format: INSERT ID=<id> Name=<name> Programme=<prog> Mark=<mark>.\n");
		return;
	}

	//take from where the target starts from. 
	//Original -> Name=sj Programme=cyber Mark=23.2
	//namePosition -> sj Programme=cyber Mark=23.2 
	//progPosition -> Programme=cyber Mark=23.2
	//markPosition -> Mark=23.2
	char* namePosition = strstr(cmdLine, "Name=");
	char* progPosition = strstr(cmdLine, "Programme=");
	char* markPosition = strstr(cmdLine, "Mark=");

	//if name is null
	if (namePosition == NULL) {
		while (1) {
			//ask for a name again
			printf("%s: Enter Name: ", userName);
			fgets(name, sizeof(name), stdin);
			//remove any whitespace
			name[strcspn(name, "\n")] = 0;

			if (strlen(name) > 0) break;
		}
	}
	else {
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
	//if no programme
	if (progPosition == NULL) {
		while (1) {
			//ask again
			printf("%s: Enter Programme: ", userName);
			fgets(programme, sizeof(programme), stdin);
			programme[strcspn(programme, "\n")] = 0;
			if (strlen(programme) > 0) break;
		}

	}
	else {
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

	if (markPosition == NULL) {
		//keep asking until get correct marks
		while (1) {
			printf("%s: Enter Marks: ", userName);
			fgets(markStr, sizeof(markStr), stdin);
			markStr[strcspn(markStr, "\n")] = 0;
			//check if numeric
			if (sscanf(markStr, "%f", &mark) != 1) {
				printf("CMS: Error - Mark must be a number.\n");
			}
			//score from 0 to 100
			else if (mark < 0.0 || mark > 100.0) {
				printf("CMS: Error - Mark must be between 0 and 100.\n");
			}
			else {
				break;
			}
		}
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

	//oppen file in read
	FILE* fptr = fopen(fileName, "r");
	char line[512];

	//ignore header
	fgets(line, sizeof(line), fptr);

	//save into line read from fptr
	while (fgets(line, sizeof(line), fptr)) {
		int existingID;
		//retrieve the existing ID from index 0 to |, since ID is front
		sscanf(line, "%d|", &existingID);
		//compare
		if (existingID == id) {
			printf("CMS: The record with ID=%d already exists.", id);
			fclose(fptr);
			return;
		}
	}
	fclose(fptr);

	//append mode
	FILE* fptr2 = fopen(fileName, "a");
	//check if got such file or not
	if (fptr2 == NULL) {
		printf("CMS: Database is not open.Use OPEN command first.\n");
		return;
	}
	//insert the data into fptr2 
	fprintf(fptr2, "%d|%s|%s|%.1f\n", id, name, programme, mark);
	//appended into the file
	fclose(fptr2);
	printf("CMS: A new record with ID=%d is successfully inserted.\n", id);
}