#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd_319, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creation of socket file descriptor
    if ((server_fd_319 = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to local the host: 8080
    if (bind(server_fd_319, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listening for incoming client connections
    if (listen(server_fd_319, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accepting the connection
    if ((new_socket = accept(server_fd_319, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    int num, sum = 0;

    // Receiving the values from the client
    while (1) {
        recv(new_socket, &num, sizeof(num), 0);
        if (num == 0) {
            break;
        }
        sum += num;
    }

    printf("Received ZERO. Sending sum back to client...\n");

    // Sending the summation values to the client
    send(new_socket, &sum, sizeof(sum), 0);

    return 0;
}
