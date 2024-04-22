#include "lib/parsehttpcontent.h"
#include "lib/stringutil.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void parseRequestLine(HttpContent *content, char *headerLine);
void parseHeaders(HttpContent *content, char *line);

HttpContent *parseHttpContent(char *buf, size_t bufsize) {
  // Allocate memory for the HttpContent struct that will be returned by the end
  // of this function
  struct HttpContent *c = malloc(sizeof(struct HttpContent));
  // Parse the values of the HTTP Request
  // Definition of HTTP Request
  // <METHOD> <PATH> <HTTPVERSION>
  // <HEADERNAME>: <VALUE>
  // \r\n
  // \r\n
  // <BODY>

  // Split elements by newlines
  char *newline = "\r\n";
  int lines_count = 0;
  char **lines = split(buf, newline, &lines_count);

  for (int i = 0; i < lines_count; i++) {
    if (i == 0) {
      parseRequestLine(c, lines[i]);
      continue;
    }
    parseHeaders(c, lines[i]);
  }

  return c;
}

void parseRequestLine(HttpContent *content, char *line) {
  char *space = " ";
  int element_count = 0;
  char **elements = split(line, space, &element_count);

  for (int i = 0; i < element_count; i++) {
    switch (i) {
    case REQ_METHOD:
      strcpy(content->m_method, elements[i]);
      break;
    case REQ_PATH:
      strcpy(content->m_path, elements[i]);
      break;
    case REQ_VERSION:
      strcpy(content->m_version, elements[i]);
      break;
    }
  }
}

void parseHeaders(HttpContent *content, char *line) {
  char *colon = ":";
  int count = 0;
  char **elements = split(line, colon, &count);

  if (count != 2) {
    return;
  } else {
    for (int i = 0; i < count; i++) {
      content->m_headers[i] = line;
    }
  }
}
