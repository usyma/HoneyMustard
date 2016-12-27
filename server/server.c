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
int num_clients; // tracks number of clients
int clients[64]; // client file descriptors, arbitrarily holds 64
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/**
** Closes the server when called by signal handler
**/
void stop_server(){
  stop = 1;
  shutdown(serverSocket, SHUT_RDWR);
  close(serverSocket);
  exit(1);
}

/**
** TODO: Read data from client and update main buffer
**/
void read_from_client(void * args){

}

/**
** TODO: Send data to all clients
**/
void send_to_clients(void * args){

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
    printf("Waiting for connection...\n");
    clients[num_client] = accept(sock_fd, NULL, NULL);
    printf("Connection made: client_id: %d, client_fd=%d\n", num_client, clients[num_client]);

    pthread_mutex_lock(&mtx);
    num_clients++;
    pthread_mutex_unlock(&mtx);

    // TODO: Create threads that will read from clients and send to clients
  }

}

int main(int argc, char ** argv){
  signal(SIGINT, stop_server);
  run_server(argv[1]);

  return 0;
}
