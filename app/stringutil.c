#include "lib/stringutil.h"
#include <stdlib.h>
#include <string.h>

char **split(char *string, char *seperators, int *count) {
  int len = strlen(string);

  *count = 0;

  int i = 0;
  while (i < len) {
    // Step though seperator
    while (i < len) {
      if (strchr(seperators, string[i]) == NULL)
        break;
      i++;
    }
    // Step through substring
    int old_i = i;
    while (i < len) {
      if (strchr(seperators, string[i]) != NULL)
        break;
      i++;
    }
    // only increment count if substing was actually present (i > old_i)
    // e.g. end of string where it would not incremement
    if (i > old_i) {
      *count = *count + 1;
    }
  }

  // Allocate space for the char array
  char **strings = malloc(sizeof(char *) * *count);

  i = 0;
  char buffer[16384];
  int string_index = 0;
  while (i < len) {
    // Step though seperator
    while (i < len) {
      if (strchr(seperators, string[i]) == NULL)
        break;
      i++;
    }

    // Step through substring and store it this time
    int j = 0;
    while (i < len) {
      if (strchr(seperators, string[i]) != NULL)
        break;

      buffer[j] = string[i];
      i++;
      j++;
    }
    buffer[j] = '\0';
    if (j > 0) {
      // dynamically allocate memory
      int to_allocate = sizeof(char) * (strlen(buffer) + 1);
      strings[string_index] = malloc(to_allocate);

      strcpy(strings[string_index], buffer);

      string_index++;
    }
  }

  return strings;
}
