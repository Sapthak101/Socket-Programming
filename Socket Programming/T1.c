//server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 12345
#define BUFFER_SIZE 256

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        socklen_t client_addr_len = sizeof(client_addr);

        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
            perror("Error accepting connection");
            continue;
        }

        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == -1) {
            perror("Error receiving data");
            close(client_socket);
            continue;
        }

        buffer[bytes_received] = '\0'; 

        struct in_addr ip_addr;
        inet_aton(buffer, &ip_addr);
        struct hostent *host_info = gethostbyaddr(&ip_addr, sizeof(ip_addr), AF_INET);

        if (host_info == NULL) {
            perror("Error getting host information");
            close(client_socket);
            continue;
        }

        ssize_t bytes_sent = send(client_socket, host_info->h_name, strlen(host_info->h_name), 0);
        if (bytes_sent == -1) {
            perror("Error sending data");
        }
    
        close(client_socket);
    }

    close(server_socket);

    return 0;
}
