#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this to the server's IP address

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    // Input message
    printf("Enter a message to send to the server: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send message to the server
    send(client_socket, buffer, strlen(buffer), 0);

    // Receive character count from the server
    int char_count;
    recv(client_socket, &char_count, sizeof(int), 0);
    printf("The server responded with the character count: %d\n", char_count);

    close(client_socket);

    return 0;
}