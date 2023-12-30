#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_socket_319, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[MAX_BUFFER_SIZE];

    // Creation of the socket
    server_socket_319 = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_319 < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Binding of the socket
    if (bind(server_socket_319, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in binding");
        exit(1);
    }

    // Listening to the connections
    if (listen(server_socket_319, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Error in listening");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_socket = accept(server_socket_319, (struct sockaddr*)&new_addr, &addr_size); // Accept connection

    // Reading message from the client
    recv(new_socket, buffer, sizeof(buffer), 0);
    printf("Received message from client: %s\n", buffer);

    // Sending the number of characters back to the client
    int char_count = strlen(buffer); //strlen used to count the number of characters
    send(new_socket, &char_count, sizeof(int), 0);

    close(new_socket);
    close(server_socket_319);

    return 0;
}