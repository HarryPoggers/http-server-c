#include "lib/http_response.h"
#include <stdio.h>
#include <string.h>

char *getPlainReturnValue(char *statusline, char *content) {
  char *returnValue;
  sprintf(returnValue,
          "%sContent-Type: text/plain\r\nContent-Length: %lu\r\n\r\n%s\r\n",
          statusline, strlen(content), content);

  return returnValue;
}
