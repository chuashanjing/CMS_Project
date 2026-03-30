#include <stdio.h>
#include "handler.h"
//
//int fileOpened = 0;

//int printDeclaration() {
//
//	printf("Declaration\n");
//	printf("Students are not allowed to copy assessment solutions from another person or other places, including AI platforms or tools.\n");
//	printf("It is the students’ responsibility to guarantee that their solutions are their own work.\n");
//	printf("Meanwhile, the students must also ensure that their work is not accessible by others.\n");
//	printf("Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n");
//	printf("\n");
//
//	printf("We hereby declare that:\n");
//	printf("* We fully understand and agree to the abovementioned policy.\n");
//	printf("* We did not copy any materials from others or from other places, e.g., AI platforms or tools.\n");
//	printf("* We did not share our materials with others or upload to any other places for public access.\n");
//	printf("* We agree that we will not disclose any information or material of the team project to others or upload to any other places for public access.\n");
//	printf("* We agree that our project will receive Zero mark if any misalignment with the abovementioned policies is detected.\n");
//
//	printf("Declared by : Group 6\n");
//	printf("Team members :\n");
//	printf("1. Chua Shan Jing\n2. Caleb Kee\n3. Kerlwin Wong\n4. Lim Wei Chen\n5. Joel Chin\n");
//	printf("Date: 9/3/2025\n");
//	printf("\n");
//}
//
//int handleOpen(char* fileName) {
//	FILE* fptr;
//
//	//read file
//	fptr = fopen(fileName, "r");
//	//if no file, create file
//	if (fptr == NULL) {
//		fptr = fopen(fileName, "w");
//		if (fptr == NULL) {
//			printf("CMS: The file is not opened.\n");
//			return;
//		}
//		else {
//			//to write into file stream
//			fprintf(fptr, "ID|Name|Programme|Mark\n");
//			fclose(fptr);
//			printf("CMS: The file \"%s\" created successfully.\n", fileName);
//		}
//	}
//	else {
//		fclose(fptr);
//	}
//
//	printf("CMS: The database file \"%s\" is successfully opened.", fileName);
//	fileOpened = 1;
//	return;
//}
//
//int handleShowAll(char* fileName) {
//	// check if file open
//	if (!fileOpened) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//
//	//open file in read mode
//	FILE* fptr = fopen(fileName, "r");
//	if (!fptr) {
//		printf("CMS: Error - Could not open file %s.\n", fileName);
//		return 0;
//	}
//
//	// Initialize variables to store the data read from the file
//	int id;
//	char name[100], programme[100], file_name[100];
//	float mark;
//	char line[512];
//
//	// Reads the first line so that the following while loop does not read it.
//	(fgets(line, sizeof(line), fptr));
//	printf("%-10s | %-15s | %-15s | %-5s\n", "ID", "Name", "Programme", "Mark"); //Prints column headers.
//
//	// Loop throw every row of file, while checking 4 items are read
//	while (fscanf(fptr, "%d | %[^|] | %[^|] | %f", &id, name, programme, &mark) == 4) {
//		//Prints the data in a formatted way, with specific width for each column.
//		printf("%-10d | %-15s | %-15s | %-5.1f\n", id, name, programme, mark);
//	}
//
//	//close file
//	fclose(fptr);
//}
//
//int handleInsert(char* cmdLine, char* fileName, char* userName) {
//	//check if file open
//	if (!fileOpened) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//
//	//if user only type INSERT, tell them error and format
//	if (strlen(cmdLine) <= 6) {
//		printf("CMS: Invalid format. Format: INSERT ID=<id> Name=<name> Programme=<prog> Mark=<mark>.\n");
//		return;
//	}
//
//	int id;
//	char name[100] = "";
//	char programme[100] = "";
//	float mark;
//	char idStr[20] = "";
//	char markStr[20] = "";
//
//	//check if ID is a number
//	if (sscanf(cmdLine, "INSERT ID=%d", &id) != 1) {
//		printf("CMS: Make sure ID does not contain any alphabets. Format: INSERT ID=<id> Name=<name> Programme=<prog> Mark=<mark>.\n");
//		return;
//	}
//
//	//take from where the target starts from. 
//	//Original -> Name=sj Programme=cyber Mark=23.2
//	//namePosition -> sj Programme=cyber Mark=23.2 
//	//progPosition -> Programme=cyber Mark=23.2
//	//markPosition -> Mark=23.2
//	char* namePosition = strstr(cmdLine, "Name=");
//	char* progPosition = strstr(cmdLine, "Programme=");
//	char* markPosition = strstr(cmdLine, "Mark=");
//
//	//if name is null
//	if (namePosition == NULL) {
//		while (1) {
//			//ask for a name again
//			printf("%s: Enter Name: ", userName);
//			fgets(name, sizeof(name), stdin);
//			//remove any whitespace
//			name[strcspn(name, "\n")] = 0;
//
//			if (strlen(name) > 0) break;
//		}
//	}
//	else {
//		//ignore the 'Name='
//		namePosition += 5; // [ Name=sj Programme=cyber Mark=23.2 ] -> [ sj Programme=cyber Mark=23.2 ]
//		char* nameEnd = progPosition;
//
//		if (nameEnd == NULL) nameEnd = markPosition;
//		if (nameEnd == NULL) {
//			strcpy(name, namePosition);
//		}
//		else {
//			//from nameposition to end of name remove, result is the name target
//			int nameTarget = nameEnd - namePosition - 1; //left with 'sj ' -1 becomes 'sj'
//
//			//name is destination, namePosition is source, and nameTarget is the length
//			//so nameTarget is 2, means from namePosition take 0 1 index, taking 'sj'
//			strncpy(name, namePosition, nameTarget); //strncpy copies specifics, strcpy copies entire
//			name[nameTarget] = '\0';
//		}
//
//		if (strlen(name) == 0) {
//			while (1) {
//				printf("%s: Enter Name: ", userName);
//				fgets(name, sizeof(name), stdin);
//				name[strcspn(name, "\n")] = 0;
//				if (strlen(name) > 0) break;
//			}
//		}
//
//	}
//	//if no programme
//	if (progPosition == NULL) {
//		while (1) {
//			//ask again
//			printf("%s: Enter Programme: ", userName);
//			fgets(programme, sizeof(programme), stdin);
//			programme[strcspn(programme, "\n")] = 0;
//			if (strlen(programme) > 0) break;
//		}
//
//	}
//	else {
//		//skip Programme=
//		progPosition += 10;
//		char* progEnd = markPosition;
//		if (progEnd == NULL) {
//			strcpy(programme, progPosition);
//		}
//		else {
//			//end of programme - programme position gives the length of the target -1, to remove space.
//			int progTarget = progEnd - progPosition - 1;
//			strncpy(programme, progPosition, progTarget);
//			programme[progTarget] = '\0';
//		}
//		if (strlen(programme) == 0) {
//			while (1) {
//				printf("%s: Enter Programme: ", userName);
//				fgets(programme, sizeof(programme), stdin);
//				programme[strcspn(programme, "\n")] = 0;
//				if (strlen(programme) > 0) break;
//			}
//		}
//	}
//
//	if (markPosition == NULL) {
//		//keep asking until get correct marks
//		while (1) {
//			printf("%s: Enter Marks: ", userName);
//			fgets(markStr, sizeof(markStr), stdin);
//			markStr[strcspn(markStr, "\n")] = 0;
//			//check if numeric
//			if (sscanf(markStr, "%f", &mark) != 1) {
//				printf("CMS: Error - Mark must be a number.\n");
//			}
//			//score from 0 to 100
//			else if (mark < 0.0 || mark > 100.0) {
//				printf("CMS: Error - Mark must be between 0 and 100.\n");
//			}
//			else {
//				break;
//			}
//		}
//	}
//	else {
//		//skip Mark=
//		markPosition += 5;
//		//check if its numeric
//		if (strlen(markPosition) == 0) {
//			while (1) {
//				printf("%s: Enter Marks: ", userName);
//				fgets(markStr, sizeof(markStr), stdin);
//				markStr[strcspn(markStr, "\n")] = 0;
//				if (sscanf(markStr, "%f", &mark) != 1) {
//					printf("CMS: Error - Mark must be a number.\n");
//				}
//				//check if 0-100
//				else if (mark < 0.0 || mark > 100.0) {
//					printf("CMS: Error - Mark must be between 0 and 100.\n");
//				}
//				else break;
//			}
//		}
//		else {
//			if (sscanf(markPosition, "%f", &mark) != 1) {
//				printf("CMS: Error - Mark must be a number.\n");
//				return;
//			}
//			else if (mark < 0.0 || mark > 100.0) {
//				printf("CMS: Error - Mark must be between 0 and 100.\n");
//				return;
//			}
//		}
//	}
//
//	//oppen file in read
//	FILE* fptr = fopen(fileName, "r");
//	char line[512];
//
//	//ignore header
//	fgets(line, sizeof(line), fptr);
//
//	//save into line read from fptr
//	while (fgets(line, sizeof(line), fptr)) {
//		int existingID;
//		//retrieve the existing ID from index 0 to |, since ID is front
//		sscanf(line, "%d|", &existingID);
//		//compare
//		if (existingID == id) {
//			printf("CMS: The record with ID=%d already exists.", id);
//			fclose(fptr);
//			return;
//		}
//	}
//	fclose(fptr);
//
//	//append mode
//	FILE* fptr2 = fopen(fileName, "a");
//	//check if got such file or not
//	if (fptr2 == NULL) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//	//insert the data into fptr2 
//	fprintf(fptr2, "%d|%s|%s|%.1f\n", id, name, programme, mark);
//	//appended into the file
//	fclose(fptr2);
//	printf("CMS: A new record with ID=%d is successfully inserted.\n", id);
//}
//
//int handleQuery(char* cmdLine, char* fileName) {
//	//check if file open
//	if (!fileOpened) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//
//	// check format for QUERY
//	int searchID;
//	if (sscanf(cmdLine, "QUERY ID=%d", &searchID) != 1) {
//		printf("CMS: Invalid format. Format: QUERY ID=<id>\n");
//		return;
//	}
//	FILE* fptr = fopen(fileName, "r");
//	if (!fptr) {
//		printf("CMS: Error - Could not open file %s\n", fileName);
//		return;
//	}
//
//	char line[512];
//
//	// get the records, skipping the header row
//	fgets(line, sizeof(line), fptr);
//	int id;
//	char name[100];
//	char programme[100];
//	float mark;
//	int found = 0;
//
//	while (fscanf(fptr, "%d|%[^|]|%[^|]|%f",
//		&id,
//		name,
//		programme,
//		&mark) == 4) {
//
//		if (id == searchID) {
//
//			printf("CMS: The record with ID=%d is found in the data table.\n", searchID);
//
//			printf("%-10s | %-15s | %-15s | %-5s\n",
//				"ID", "Name", "Programme", "Mark");
//
//			printf("%-10d | %-15s | %-15s | %-5.1f\n",
//				id,
//				name,
//				programme,
//				mark);
//
//			found = 1;
//			break;
//		}
//	}
//
//	if (!found) {
//		printf("CMS: The record with ID=%d does not exist.\n", searchID);
//	}
//
//	fclose(fptr);
//}
//
//int handleUpdate() {
//	//joule
//}
//
//int handleDelete(char* cmdLine, char* fileName, char* userName) {
//	// check if file open
//	if (!fileOpened) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//
//	// check format for DELETE
//	int searchID;
//	if (sscanf(cmdLine, "DELETE ID=%d", &searchID) != 1) {
//		printf("CMS: Invalid format. Format: DELETE ID=<id>\n");
//		return;
//	}
//
//	FILE* fptr = fopen(fileName, "r");
//	if (!fptr) {
//		printf("CMS: Error - Could not open file %s\n", fileName);
//		return;
//	}
//
//	char line[512];
//	char allLines[1000][512];
//	int lineCount = 0;
//	int found = 0;
//	int deleteIndex = -1;
//
//	// read header into allLines
//	fgets(allLines[lineCount], sizeof(allLines[lineCount]), fptr);
//	lineCount++;
//
//	// read remaining lines, storing each one
//	while (fgets(line, sizeof(line), fptr)) {
//		int existingID;
//		sscanf(line, "%d|", &existingID);
//		if (existingID == searchID) {
//			found = 1;
//			deleteIndex = lineCount; // remember which line to skip later
//		}
//		strcpy(allLines[lineCount], line);
//		lineCount++;
//	}
//	fclose(fptr);
//
//	// if not found, print warning
//	if (!found) {
//		printf("CMS: The record with ID=%d does not exist.", searchID);
//		return;
//	}
//
//	// reparse and print the matched line for display
//	int id;
//	char name[100], programme[100];
//	float mark;
//	sscanf(allLines[deleteIndex], "%d|%[^|]|%[^|]|%f", &id, name, programme, &mark);
//
//	// double confirm deletion
//	char confirm[10];
//	printf("CMS: Are you sure you want to delete record with ID=%d? Type 'Y' to Confirm or type 'N' to cancel.\n", id);
//	printf("%s: ", userName);
//	fgets(confirm, sizeof(confirm), stdin);
//	confirm[strcspn(confirm, "\n")] = 0;
//
//	if (strcmp(confirm, "Y") != 0) {
//		printf("CMS: Deletion cancelled. No changes were made.");
//		return;
//	}
//
//	// write all lines back except the deleted one
//	FILE* fptr2 = fopen(fileName, "w");
//	if (!fptr2) {
//		printf("CMS: Error - Could not open file %s for writing\n", fileName);
//		return;
//	}
//	for (int i = 0; i < lineCount; i++) {
//		if (i != deleteIndex) {
//			fprintf(fptr2, "%s", allLines[i]);
//		}
//	}
//	fclose(fptr2);
//
//	printf("CMS: The record with ID=%d is successfully deleted.", searchID);
//}
//
//int handleSave(char* fileName) {
//	// check if file open
//	if (!fileOpened) {
//		printf("CMS: Database is not open.Use OPEN command first.\n");
//		return;
//	}
//
//	//open file in read mode
//	FILE* fptr = fopen(fileName, "r");
//	if (!fptr) {
//		printf("CMS: Error - Could not open file %s\n", fileName);
//		return;
//	}
//
//	// Close the file after reading
//	fclose(fptr);
//	fileOpened = 0;
//	if (fileOpened == 0) {
//		printf("CMS: The database file \"%s\" is successfully saved.", fileName);
//	}
//	else {
//		printf("CMS: Error - Could not close file %s", fileName);
//		return;
//	}
//}

int main() {
	char userName[] = "P1-6";
	char filename[] = "P1-6_CMS.txt";
	FILE* fptr;


	//print declaration
	printDeclaration();

	//print command options
	printf("Type a command (OPEN, SHOW ALL, INSERT, QUERY, UPDATE, DELETE, SAVE, EXIT).\n\n");


	char cmdLine[100];
	while (1) {
		printf("%s: ", userName);
		fgets(cmdLine, sizeof(cmdLine), stdin);
		cmdLine[strcspn(cmdLine, "\n")] = 0;

		if (strcmp(cmdLine, "EXIT") == 0) {
			break;
		}
		else if (strcmp(cmdLine, "OPEN") == 0) {
			handleOpen(filename);
		}
		else if (strcmp(cmdLine, "SHOW ALL") == 0) {
			handleShowAll(filename);
		}
		else if (strncmp(cmdLine, "INSERT", 6) == 0) {
			handleInsert(cmdLine, filename, userName);
		}
		else if (strncmp(cmdLine, "QUERY", 5) == 0) {
			handleQuery(cmdLine, filename);
		}
		else if (strncmp(cmdLine, "UPDATE", 6) == 0) {
			handleUpdate(cmdLine, filename, userName);
		}
		else if (strncmp(cmdLine, "DELETE", 6) == 0) {
			handleDelete(cmdLine, filename, userName);
		}
		else if (strcmp(cmdLine, "SAVE") == 0) {
			handleSave(filename);
		}
		else {
			printf("CMS: Unknown command '%s'. Please Try again.\n", cmdLine);
		}
		printf("\n");
	}



	return 0;
}