#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket_319;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Creation of the socket
    client_socket_319 = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_319 < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this to the server's IP address

    // Connecting to the server
    if (connect(client_socket_319, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    // Inputing message
    printf("Enter a message to send to the server: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Sending message to the server
    send(client_socket_319, buffer, strlen(buffer), 0);

    // Receiving the character count from the server
    int char_count;
    recv(client_socket_319, &char_count, sizeof(int), 0);
    printf("The server responded with the character count: %d\n", char_count-1);

    //Closing the Socket 
    close(client_socket_319);

    return 0;
}