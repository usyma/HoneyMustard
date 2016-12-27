#include <errno.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* Global Variables */
int serverSocket;

/**
** Called by signal handler to close client
**/
void close_client(){

}

/**
** TODO: Read from server
**/
void read_from_server(void * args){

}

/**
** TODO: Write to server
**/
void write_to_server(void * args){

}

void run_client(char * host, char * port, char * username){
  int s;
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  if(serverSocket < 0){
    perror("socket()");
    exit(1);
  }

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET; /* IPv4 only */
  hints.ai_socktype = SOCK_STREAM; /* TCP */

  s = getaddrinfo(host, port, &hints, &result);

  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  if(connect(serverSocket, result->ai_addr, result->ai_addrlen) < 0){
    perror("connect()");
    exit(1);
  }

  pthread_create(&threads[0], NULL, read_from_server, (void*)username);
  pthread_create(&threads[1], NULL, write_to_server, (void*)username);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
}

/**
** ./client <host> <port> <username>
**/
int main(int argc, char ** argv){
  if(argc != 4){
    fprintf(stderr, "Usage: ./client <host> <port> <username>\n");
    exit(1);
  }

  signal(SIGINT, close_client);
  run_client(argv[1], argv[2], argv[3]);

  return 0;
}
