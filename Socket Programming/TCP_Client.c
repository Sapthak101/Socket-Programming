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

int main()
{
  //char *ip = "127.0.0.1";
  int port = 8080;
  
  int sock;
  struct sockaddr_in addr;
  socklen_t addr_size;
  char buffer[1024];
  int n, len=0;
  int maxLen=1024;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");
  
  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htons(INADDR_ANY);

  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
                                                          
  bzero(buffer, 1024);
  strcpy(buffer, "HELLO, THIS IS CLIENT.");
  printf("Client: %s\n", buffer);
  send(sock, buffer, strlen(buffer), 0);
                                          
  bzero(buffer, 1024);
  char* ptr = buffer;
  while (n=recv(sock, ptr, maxLen, 0)>0)
  {                                            
       ptr += n; 
       maxLen -= n;
       len += n;
  }
  printf("Server: %s\n", buffer);
  close(sock); 
  printf("Disconnected from the server.\n");

  return 0;
}