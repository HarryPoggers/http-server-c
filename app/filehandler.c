#include "lib/filehandler.h"
#include <stdio.h>
#include <stdlib.h>

char *getFileContents(char *path) {
  FILE *pF = fopen(path, "r");

  if (pF == NULL) {
    return FILE_UNABLE_TO_BE_OPENED;
  }

  fseek(pF, 0, SEEK_END);
  long fsize = ftell(pF);
  fseek(pF, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, fsize, 1, pF);
  fclose(pF);

  buffer[fsize] = 0;

  return buffer;
}
