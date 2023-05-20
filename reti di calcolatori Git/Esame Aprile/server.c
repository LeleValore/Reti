#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"

#define MAX_SECRET_LENGTH 50

struct SecretMessage {
    char client_username[3];
    char secret[MAX_SECRET_LENGTH + 1];
};

struct SecretMessage secret_message;

void send_error(int sockfd, const char* error_message) {
    send(sockfd, error_message, strlen(error_message), 0);
}

void handle_client_request(int sockfd, const char* requested_username) {
    if (strcmp(requested_username, secret_message.client_username) == 0) {
        // Found the requested username
        send(sockfd, secret_message.secret, strlen(secret_message.secret), 0);
    } else {
        // Requested username not found
        send_error(sockfd, "Error: Requested username not found");
    }
}

int main(int argc , char* argv[]) {
    int sockfd, new_sockfd;
    struct sockaddr_in addr;
    socklen_t addr_len;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        return 1;
    }

    // Set server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, SERVER_IP, &(addr.sin_addr)) <= 0) {
        perror("Invalid address");
        return 1;
    }

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error in bind");
        return 1;
    }

    // Listen for incoming connections
    if (listen(sockfd, 1) < 0) {
        perror("Error in listen");
        return 1;
    }

    // Accept client connections
    addr_len = sizeof(addr);
    new_sockfd = accept(sockfd, (struct sockaddr*)&addr, &addr_len);
    if (new_sockfd < 0) {
        perror("Error in accept");
        return 1;
    }

    // Receive client's username
    ssize_t size = recv(new_sockfd, secret_message.client_username, sizeof(secret_message.client_username) - 1, 0);
    if (size <= 0) {
        perror("Error in recv");
        close(new_sockfd);
        return 1;
    }
    secret_message.client_username[size] = '\0';

    // Receive secret message
    size = recv(new_sockfd, secret_message.secret, sizeof(secret_message.secret) - 1, 0);
    if (size <= 0) {
        perror("Error in recv");
        close(new_sockfd);
        return 1;
    }
    secret_message.secret[size] = '\0';

    // Handle client's request
    char requested_username[3];
    size = recv(new_sockfd, requested_username, sizeof(requested_username) - 1, 0);
    if (size <= 0) {
        perror("Error in recv");
        close(new_sockfd);
        return 1;
    }
    requested_username[size] = '\0';

    handle_client_request(new_sockfd, requested_username);

    close(new_sockfd);
    close(sockfd);

    return 0;
}
