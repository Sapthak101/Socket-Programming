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
	char result[MAXLINE];
	char num1[MAXLINE];
    char num2[MAXLINE];
	struct sockaddr_in servaddr;

	printf("Enter two numbers: \n");
	scanf("%s %s", num1, num2);
	
	if ( (sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
		
	int n, len;
		
	sendto(sockfd, (const char *)num1, strlen(num1), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("The first number is sent.\n");
	sendto(sockfd, (const char *)num2, strlen(num2), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	printf("The second number is sent.\n");

	n = recvfrom(sockfd, (char *)result, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
	
	result[n] = '\0';
	printf("The Server's response after adding: %s\n", result);
	
	close(sockfd);
	
	return 0;
}
