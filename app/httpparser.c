#include "lib/parsehttpcontent.h"
#include "lib/stringutil.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void parseRequestLine(HttpRequest *content, char *headerLine);
bool parseHeaders(HttpRequest *content, char *line, int headerIndex);

HttpRequest *parseHttpContent(char *buf, size_t bufsize) {
  // Allocate memory for the HttpContent struct that will be returned by the end
  // of this function
  struct HttpRequest *c = malloc(sizeof(struct HttpRequest));
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
  int headerIndex = 0;
  char **lines = split(buf, newline, &lines_count);

  char *body;

  for (int i = 0; i < lines_count; i++) {
    if (i == 0) {
      parseRequestLine(c, lines[i]);
      continue;
    } else if (strcmp(lines[i], newline) != 0) {
      if (parseHeaders(c, lines[i], headerIndex)) {
        headerIndex++;
      } else { // If it's not a header by standard, append it to the body
        // Calculate the remaining space in m_body
        size_t remaining_space = MAX_BODY_SIZE - strlen(c->m_body);
        // Ensure there's enough space to append the new line
        if (strlen(lines[i]) < remaining_space) {
          // Use strncat to safely append the new line
          strncat(c->m_body, lines[i],
                  remaining_space - 1); // Leave space for the null terminator
        } else {
          // Handle the case where there's not enough space, e.g., by truncating
          // or logging an error
        }
      }
    }
  }

  // Make sure the Memory is freed
  for (int i = 0; i < lines_count; i++) {
    free(lines[i]);
  }
  free(lines);

  return c;
}

void parseRequestLine(HttpRequest *content, char *line) {
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

  // Make sure the Memory is freed
  for (int i = 0; i < element_count; i++) {
    free(elements[i]);
  }

  free(elements);
}

bool parseHeaders(HttpRequest *content, char *line, int headerIndex) {
  char *colon = ":";
  int count = 0;
  bool done = false;
  char **elements = split(line, colon, &count);

  if (count < 2) {
    return false;
  } else {
    content->m_headers[headerIndex] =
        malloc(strlen(line) + 1); // Allocate memory to save the content in
    strcpy(content->m_headers[headerIndex],
           line); // Copy the value to the specified index
    done = true;
  }

  // Make sure the Memory is freed
  for (int i = 0; i < count; i++) {
    free(elements[i]);
  }

  free(elements);

  return done;
}
