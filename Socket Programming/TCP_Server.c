#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){

  //char *ip = "127.0.0.1";
  int port = 8080;

  int server_sock, client_sock;
  struct sockaddr_in server_addr, client_addr;
  socklen_t addr_size;
  char buffer[1024];
  int n, len=0, n1;
  int maxLen=1024;

  server_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock < 0){
    perror("Socket error");
    exit(1);
  }
  printf("TCP server socket created.\n");

  memset(&server_addr, '\0', sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = htons(INADDR_ANY); 
  
  //inet_addr(ip); //fetching actual IP address from the DNS
  /*
    The IP address 127.0. 0.1 is a special-purpose IPv4 address and is called the localhost or loopback address. All computers use this address as their own, but it doesn't let computers communicate with other devices as a real IP address does.
  */

  n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if (n < 0){
    perror("Bind error");
    exit(1);
  }
  printf("Bind to the port number: %d\n", port);

  listen(server_sock, 5);
  printf("Listening...\n");
  
  while(1){
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("Client connected.\n");

    bzero(buffer, 1024);
    char* ptr = buffer;
    while (n1=recv(server_sock, ptr, maxLen, 0)>0)
    {
       printf("Client: %s\n", buffer);
       ptr += n1; 
       maxLen -= n1;
       len += n1;
    }
    bzero(buffer, 1024);
    strcpy(buffer, "This is Server. The system is funtioning properly");
    printf("Server: %s\n", buffer);
    send(client_sock, buffer, strlen(buffer), 0);
    
    close(client_sock);
    printf("Client disconnected.\n\n");

  }

  return 0;
}