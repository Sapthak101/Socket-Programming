#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

//Computation Part
int count_vowels(const char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char c = tolower(str[i]);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
    }
    return count;
}

int main() {
    int server_socket_319, client_socket_319;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char buffer[MAX_BUFFER_SIZE];

    //Socket Creation
    server_socket_319 = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_319 == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    //Binding of the Socket
    if (bind(server_socket_319, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        close(server_socket_319);
        exit(EXIT_FAILURE);
    }

    //Listening to the Client
    if (listen(server_socket_319, 5) == -1) {
        perror("Error listening for connections");
        close(server_socket_319);
        exit(EXIT_FAILURE);
    }

    printf("Listening...\n");

    client_addr_len = sizeof(client_addr);

    //Acceppting  the connection
    client_socket_319 = accept(server_socket_319, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_socket_319 == -1) {
        perror("Error accepting connection");
        close(server_socket_319);
        exit(EXIT_FAILURE);
    }

    printf("Connection established with client\n");

    //Receiving the query
    ssize_t bytes_received = recv(client_socket_319, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        perror("Error receiving data");
        close(client_socket_319);
        close(server_socket_319);
        exit(EXIT_FAILURE);
    }

    //Conputation Logic
    buffer[bytes_received] = '\0';

    int word_count = 0;
    int char_count = 0;
    int vowel_count = count_vowels(buffer);
    char *token = strtok(buffer, " ");
    while (token != NULL) {
        word_count++;
        char_count += strlen(token);
        token = strtok(NULL, " ");
    }

    //Sending the result
    char response[100];
    snprintf(response, sizeof(response), "Words: %d, Characters: %d, Vowels: %d\n", word_count, char_count-1, vowel_count);
    send(client_socket_319, response, strlen(response), 0);

    //Closing the Socket
    close(client_socket_319);
    close(server_socket_319);

    return 0;
}