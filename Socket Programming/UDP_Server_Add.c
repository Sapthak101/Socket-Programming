#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	8080
#define MAXLINE 1024
	
int main() 
{
	int sockfd;
	char buffer[MAXLINE];
    char buffer1[MAXLINE];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	printf("The server is fully functional\n");

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = PF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	for (;;)
	{
		len = sizeof(cliaddr); //len is value/result
		
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n] = '\0';
		printf("Client : %s\n", buffer);
		int num1=atoi(buffer);

        n = recvfrom(sockfd, (char *)buffer1, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
		buffer[n]='\0';
		printf("Client : %s\n", buffer1);
        int num2=atoi(buffer1);

        int num3=num1+num2;
        char result[MAXLINE];
        sprintf(result, "%d", num3);

        sendto(sockfd, (const char *)result, strlen(result), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
		printf("The addition is done and the response is sent to the client\n");
	}

	return 0;
}