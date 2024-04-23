#include "lib/http_response.h"
#include "lib/stringutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getResponseCodeValue(char *statusline) {
  char *returnValue = (char *)malloc(strlen(statusline) + 1);
  if (returnValue == NULL) {
    return NULL;
  }

  sprintf(returnValue, "%s\r\n", statusline);

  return returnValue;
}

char *getPlainReturnValue(char *statusline, char *content) {
  // Calculate the length of the HTTP headers and separators
  size_t headersLength =
      strlen("Content-Type: text/plain\r\nContent-Length: \r\n\r\n\r\n");
  // Calculate the total length needed for the return value
  size_t totalLength = strlen(statusline) + strlen(content) + headersLength;
  // Allocate memory for the return value
  char *returnValue = (char *)malloc(totalLength); // +1 for the null terminator
  if (returnValue == NULL) {
    // Handle memory allocation failure
    return NULL;
  }
  // Use sprintf to format the return value
  sprintf(returnValue,
          "%sContent-Type: text/plain\r\nContent-Length: %lu\r\n\r\n%s\r\n",
          statusline, strlen(content), content);

  return returnValue;
}
