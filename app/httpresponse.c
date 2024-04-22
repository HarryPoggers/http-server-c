#include "lib/http_response.h"
#include <stdio.h>
#include <string.h>

char *getPlainReturnValue(char *statusline, char *content) {
  char *returnValue;
  sprintf(returnValue,
          "%s\r\nContent-Type: text/plain\r\nContent-Length: %lu\r\n%s",
          statusline, strlen(content), content);
  return returnValue;
}
