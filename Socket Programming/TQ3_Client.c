#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int client_socket_319;
    struct sockaddr_in server_addr;
    char input_string[MAX_BUFFER_SIZE];

    //Socket Creation
    client_socket_319 = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_319 == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    //Connection to the Server
    if (connect(client_socket_319, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        close(client_socket_319);
        exit(EXIT_FAILURE);
    }

    printf("Enter a string: ");
    fgets(input_string, sizeof(input_string), stdin);

    //Sending the query
    send(client_socket_319, input_string, strlen(input_string), 0);

    //Response from the Server
    char response[MAX_BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket_319, response, sizeof(response), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
    } else {
        response[bytes_received] = '\0';
        printf("Server response: %s\n", response);
    }

    //Closing the Socket
    close(client_socket_319);

    return 0;
}