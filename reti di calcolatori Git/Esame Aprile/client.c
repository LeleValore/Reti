#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5000

void request_secret(const char* client_username, const char* requested_username) {
    int sockfd;
    struct sockaddr_in addr;
    ssize_t size;
    char responce[1024];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        return;
    }

    // Set server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(addr.sin_addr)) <= 0) {
        perror("Invalid address");
        return;
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error in connect");
        return;
    }

    // Send client's username
    send(sockfd, client_username, strlen(client_username), 0);

    // Send requested username
    send(sockfd, requested_username, strlen(requested_username), 0);

    // Receive server response
    size = recv(sockfd, responce, sizeof(responce) - 1, 0);
    if (size < 0) {
        perror("Error in recv");
        return;
    }
    responce[size] = '\0';

    // Display server response
    printf("Server response: %s\n", responce);

    close(sockfd);
}

int main() {
    const char* client_username = "C1";
    const char* requested_username = "C2";

    request_secret(client_username, requested_username);

    return 0;
}
