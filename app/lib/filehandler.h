#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdbool.h>

#define FILE_UNABLE_TO_BE_OPENED "Unable to open file"

char *getFileContents(char *path);
bool writeToFile(char *path, char *content);

#endif // !FILE_HANDLER_H
