#include "lib/filehandler.h"
#include <stdio.h>
#include <stdlib.h>

char *getFileContents(char *path) {
  FILE *f = fopen(path, "r");

  if (f == NULL) {
    return FILE_UNABLE_TO_BE_OPENED;
  }

  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buffer = malloc(fsize + 1);
  fread(buffer, fsize, 1, f);
  fclose(f);

  buffer[fsize] = 0;

  printf("Content of File: %s", buffer);

  return buffer;
}
