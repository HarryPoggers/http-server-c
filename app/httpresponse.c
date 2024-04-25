#include "lib/filehandler.h"
#include "lib/http_response.h"
#include "lib/http_response_line.h"
#include "lib/stringutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getResponseCodeValue(char *statusline) {
  char *contentLengthHeader = "Content-Length: 0\r\n";

  char *returnValue =
      (char *)malloc(strlen(statusline) + strlen(contentLengthHeader) + 1);
  if (returnValue == NULL) {
    return NULL;
  }

  sprintf(returnValue, "%s%s\r\n", statusline, contentLengthHeader);

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

char *getOctetStreamResponse(char *statusline, char *filePath) {
  char *headers = "Content-Type: application/octet-stream\r\nContent-Length: ";
  size_t headersLength = strlen(headers + 1);

  char *fileContent = getFileContents(filePath);
  size_t contentLength;
  if (strcmp(fileContent, FILE_UNABLE_TO_BE_OPENED)) {
    statusline = HTTP_STATUSLINE_NOT_FOUND;
    contentLength = 0;
  } else {
    contentLength = strlen(fileContent);
  }

  size_t totalLength = headersLength + contentLength;

  char *returnValue = (char *)malloc(totalLength + 1);
  if (returnValue == NULL) {
    return NULL;
  }

  sprintf(returnValue, "%s%s\r\n%lu\r\n%s", statusline, headers, contentLength,
          fileContent);

  return returnValue;
}
