#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     // For close(), read(), write()
#include <arpa/inet.h>  // For sockaddr_in, inet_pton, htons, etc.

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;   // stores server IP address and port
    char buffer[BUFFER_SIZE];       // store data received from server
    FILE *fp;                       

    // Create TCP socket (AF_INET = IPv4, SOCK_STREAM = TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Fill server address structure: IPv4 + port
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);   // Convert port to network byte order

    // Convert IP string ("127.0.0.1") to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }

    // Connect to server 
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");

    // Receive hello message
    
    ssize_t bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';          // Null-terminate to print as string
        printf("Message from server: %s\n", buffer);
    }

    // save received data
    fp = fopen("received.txt", "wb");
    if (fp == NULL) {
        perror("File open error");
        close(sock);
        exit(1);
    }

    // Keep receiving the rest of the data until server closes connection
    while ((bytesReceived = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytesReceived, fp);
    }

    fclose(fp);
    printf("File received as 'received.txt'.\n");

    // Close the TCP connection
    close(sock);
    return 0;
}
