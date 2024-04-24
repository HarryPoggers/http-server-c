#include "lib/arrayutil.h"
#include "lib/http_response.h"
#include "lib/http_response_line.h"
#include "lib/parsehttpcontent.h"
#include "lib/routes.h"
#include "lib/stringutil.h"
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void *handleRequest(void *client_fd);

int main() {
  // Disable output buffering
  setbuf(stdout, NULL);

  int server_fd, client_addr_len;

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

  while (true) {

    struct sockaddr_in client_addr;

    printf("Waiting for a client to connect...\n");
    client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                           (socklen_t *)&client_addr_len);
    if (client_fd < 0) {
      printf("Accept failed: %s\n", strerror(errno));
      return 1;
    }
    printf("Client connected\n");

    pthread_t t;
    printf("Creating thread for request\n");
    if (pthread_create(&t, NULL, handleRequest, (void *)&client_fd) != 0) {
      printf("Failed to create thread to handle request data\n");
      close(client_fd);
      continue; // Skip to the next iteration
    }

    pthread_detach(
        t); // Detach from the thread to allow it to clean up after itself
  }

  close(server_fd);

  return 0;
}

void *handleRequest(void *data) {
  char *toSend;
  int client_fd = *(int *)data;

  char buffer[BUFFER_SIZE];
  int bytes_read = recv(client_fd, buffer, sizeof(buffer), 0);

  printf("Received %d bytes from %d\n", bytes_read, client_fd);

  if (bytes_read < 0) {
    close(client_fd);
    return NULL;
  }

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
    toSend = getResponseCodeValue(HTTP_STATUSLINE_OK);
  } else if (strncmp(request.m_path, ECHO_ROUTE, strlen(ECHO_ROUTE)) == 0) {
    char *returnvalue = strstr(request.m_path, ECHO_ROUTE);
    returnvalue += strlen(ECHO_ROUTE);
    toSend = getPlainReturnValue(HTTP_STATUSLINE_OK, returnvalue);
  } else if (strcmp(request.m_path, USER_AGENT_ROUTE) == 0) {
    char toSearch[] = "User-Agent:";
    for (int i = 0; i < ARRAYLENGTH(request.m_headers); i++) {
      if (request.m_headers[i] != NULL) {
        if (strncmp(request.m_headers[i], toSearch, strlen(toSearch)) == 0) {
          int count = 0;
          char *seperators = ": ";
          char **parts = split(request.m_headers[i], seperators, &count);
          if (count == 2) {
            toSend = getPlainReturnValue(HTTP_STATUSLINE_OK, parts[1]);
          }
        }
      }
    }
  } else {
    toSend = getResponseCodeValue(HTTP_STATUSLINE_NOT_FOUND);
  }

  if (toSend != NULL) {
    printf("***********Sending Back to %d************\n%s\n***********Sending "
           "Back************\n",
           client_fd, toSend);
    send(client_fd, toSend, strlen(toSend), 0);
  }

  close(client_fd);

  return NULL;
}
