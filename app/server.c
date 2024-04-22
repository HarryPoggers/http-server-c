#include "lib/arrayutil.h"
#include "lib/http_response.h"
#include "lib/http_response_line.h"
#include "lib/parsehttpcontent.h"
#include "lib/routes.h"
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  // Disable output buffering
  setbuf(stdout, NULL);

  int server_fd, client_addr_len;
  struct sockaddr_in client_addr;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    printf("Socket creation failed: %s...\n", strerror(errno));
    return EXIT_FAILURE;
  }

  // Since the tester restarts your program quite often, setting REUSE_PORT
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) <
      0) {
    printf("SO_REUSEPORT failed: %s \n", strerror(errno));
    return EXIT_FAILURE;
  }

  struct sockaddr_in serv_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(4221),
      .sin_addr = {htonl(INADDR_ANY)},
  };

  if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
    printf("Bind failed: %s \n", strerror(errno));
    return EXIT_FAILURE;
  }

  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    printf("Listen failed: %s \n", strerror(errno));
    return EXIT_FAILURE;
  }

  printf("Waiting for a client to connect...\n");
  client_addr_len = sizeof(client_addr);

  int client_fd =
      accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
  printf("Client connected\n");

  char buffer[BUFFER_SIZE];
  int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);

  printf("Received %d bytes\n", bytes_read);

  HttpRequest request = *parseHttpContent(buffer, bytes_read);

  printf("Received Method: %s\t Received Path: %s\t Received Version: %s\n\n",
         request.m_method, request.m_path, request.m_version);

  for (int i = 0; i < ARRAYLENGTH(request.m_headers); i++) {
    if (request.m_headers[i] != NULL) {
      printf("Header %d:\t%s\n", i, request.m_headers[i]);
    }
  }
  printf("\n");

  printf("Body:\t%s\n", request.m_body);

  if (strcmp(request.m_path, "/") == 0) {
    send(client_fd, HTTP_STATUSLINE_OK, strlen(HTTP_STATUSLINE_OK), 0);
  } else if (strncmp(request.m_path, ECHO_ROUTE, strlen(ECHO_ROUTE)) == 0) {
    char *returnvalue;
    int startIndex = strlen(ECHO_ROUTE) - 1;
    int endIndex = strlen(request.m_path) - strlen(ECHO_ROUTE);
    printf("Getting Value from '%s' from index %d to end index %d\n",
           request.m_path, startIndex, endIndex);
    // TODO: Make this work.
    strncpy(returnvalue, request.m_path + (strlen(ECHO_ROUTE)),
            strlen(request.m_path) - strlen(ECHO_ROUTE) + 1);
    char *toSend = getPlainReturnValue(HTTP_STATUSLINE_OK, returnvalue);
    send(client_fd, toSend, strlen(toSend), 0);
  } else {
    send(client_fd, HTTP_STATUSLINE_NOT_FOUND,
         strlen(HTTP_STATUSLINE_NOT_FOUND), 0);
  }

  close(server_fd);

  return 0;
}
