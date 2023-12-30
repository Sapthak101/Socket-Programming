#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int port = 5545;

    // Initialization
    int server_sock, client_sock[8], maxfd, i;
    struct sockaddr_in servaddr, clieaddr;
    char buffer[1024];
    socklen_t addr_size;
    int n;
    fd_set readfd, allfd;

    // Socket creation
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed.");
        exit(1);
    }

    // Set port and address
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Binding
    n = bind(server_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (n < 0) {
        perror("Binding error");
        exit(-1);
    }

    // Listening
    listen(server_sock, 8);
    printf("Listening...\n");

    // Macros define
    FD_ZERO(&allfd);
    FD_SET(server_sock, &allfd);
    maxfd = server_sock + 1;

    i = 0;
    addr_size = sizeof(clieaddr);

    while (1) {
        readfd = allfd;
        int k = select(maxfd, &readfd, NULL, NULL, NULL);

        if (FD_ISSET(server_sock, &readfd)) {
            client_sock[i] = accept(server_sock, (struct sockaddr*)&clieaddr, &addr_size);
            FD_SET(client_sock[i], &allfd);
            if (maxfd <= client_sock[i]) {
                maxfd = client_sock[i] + 1;
            }
            i++;
        }

        // Message transfer and processing
        for (int j = 0; j < i; j++) {
        if (FD_ISSET(client_sock[j], &readfd)) {
        int r = recv(client_sock[j], buffer, sizeof(buffer), 0);

        if (r == 0) {
            close(client_sock[j]);
            FD_CLR(client_sock[j], &allfd);
        } else {
            printf("Received message from client: %s\n", buffer);
            char* msg = "Hello!";
            send(client_sock[j], msg, strlen(msg), 0);
            
        }
       
    }
     
}

}
    return 0;
}