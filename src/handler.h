// Global variable declaration
extern int fileOpened;

// Function prototypes
int printDeclaration();
int handleOpen(char* fileName);
int handleShowAll(char* fileName);
int handleInsert(char* cmdLine, char* fileName, char* userName);
int handleQuery(char* cmdLine, char* fileName);
int handleUpdate(char* cmdLine, char *filename, char *userName);
int handleDelete(char* cmdLine, char* fileName, char* userName);
int handleSave(char* fileName);