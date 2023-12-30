#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    struct sockaddr_in server_address;
    int sock_319 = 0, num;
    char *hello = "ZERO";
    int sum;

    // Creation of socket
    if ((sock_319 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form, to make them adjustable with the networking address format
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connecting to server
    if (connect(sock_319, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // Receiving values from the user and sending it back to the server
    while (1) {
        printf("Enter a number (or ZERO to end): ");
        scanf("%d", &num);

        send(sock_319, &num, sizeof(num), 0);

        if (num == 0) {
            break;
        }
    }

    // Sending "ZERO" to the server
    send(sock_319, hello, strlen(hello), 0);

    // Receiving the summation from the server
    recv(sock_319, &sum, sizeof(sum), 0);
    printf("Sum received from server: %d\n", sum);

    return 0;
}
