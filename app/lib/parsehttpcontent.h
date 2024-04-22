#ifndef PARSE_HTTP_CONTENT_H
#define PARSE_HTTP_CONTENT_H

#include <stddef.h>

#define MAX_BODY_SIZE 1024

typedef struct HttpRequest {
  char m_method[10];
  char m_path[255];
  char m_version[20];
  char *m_headers[255];
  char m_body[MAX_BODY_SIZE];
} HttpRequest;

typedef enum HttpRequestStructure {
  REQ_METHOD = 0,
  REQ_PATH = 1,
  REQ_VERSION = 2
} HttpRequestStructure;

/*
 * parseHttpContent will return a HttpContent object to easily access the
 * vairables within
 * @param char *buf the buffer of received data
 * @param size
 * @return a pointer to the parsed HttpContent
 */
HttpRequest *parseHttpContent(char *buf, size_t bufsize);

#endif // !PARSE_HTTP_CONTENT_H
