#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    char *ip = "127.0.0.1";
    int port = 5545;

    int sock;
    struct sockaddr_in addr;
    char buff[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed.");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Connection failed.");
        close(sock);
        exit(1);
    }

    printf("Connected to Server.\n");

    strcpy(buff, "Hello Server!");
    send(sock, buff, strlen(buff), 0);
    printf("Message sent successfully.\n");
    recv(sock, buff, 1023, 0);
    printf("Received message from server %s\n", buff);

    return 0;
}