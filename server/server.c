#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

/* Global Variables */
int stop;
int serverSocket; // server file descriptor

/**
** Closes the server when called by signal handler
**/
void stop_server(){
  stop = 1;
  shutdown(serverSocket, SHUT_RDWR);
  close(serverSocket);
  exit(1);
}

void run_server(char * port){
  int s;
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);

  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }

  if (listen(sock_fd, 10) != 0) {
    perror("listen()");
    exit(1);
  }

  while(!stop){
    // TODO: Create data structure to keep track of multiple clients

    printf("Waiting for connection...\n");
    int client_fd = accept(sock_fd, NULL, NULL);
    printf("Connection made: client_fd=%d\n", client_fd);

    char buffer[1000];
    int len = read(client_fd, buffer, sizeof(buffer) - 1);
    buffer[len] = '\0';

    printf("Read %d chars\n", len);
    printf("===\n");
    printf("%s\n", buffer);
  }

}

int main(int argc, char ** argv){
  signal(SIGINT, stop_server);
  run_server(argv[1]);

  return 0;
}
