#ifndef PARSE_HTTP_CONTENT_H
#define PARSE_HTTP_CONTENT_H

#include <stddef.h>

typedef struct HttpContent {
  char *m_path;
  char *m_method;
  char **m_headers;
} HttpContent;

/*
 * parseHttpContent will return a HttpContent object to easily access the
 * vairables within
 * @param char *buf the buffer of received data
 * @param size
 * @return a pointer to the parsed HttpContent
 */
HttpContent *parseHttpContent(char *buf, size_t bufsize);

#endif // !PARSE_HTTP_CONTENT_H
