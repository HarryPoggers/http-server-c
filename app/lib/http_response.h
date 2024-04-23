#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

char *getResponseCodeValue(char *statusline);
char *getPlainReturnValue(char *statusline, char *content);

#endif // !HTTP_RESPONSE_H
