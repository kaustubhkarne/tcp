#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>    
#include <unistd.h>     // For close(), sleep()
#include <arpa/inet.h>  // For sockaddr_in, htons, etc.

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;     // server IP+port info
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];       // Buffer used while reading file and sending data
    FILE *fp;                      

    // Create TCP socket 
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(1);
    }

    // Fill address structure: IPv4, listen on any local IP, chosen port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons(PORT);        

    // Bind socket to the given IP and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Mark the socket as a passive socket to listen for incoming connection requests
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(1);
    }
    printf("Server listening on port %d...\n", PORT);

    // Block and wait for a client connection; returns a new socket for that client
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(1);
    }
    printf("Client connected.\n");

    // Send Hello message 
    char *msg = "Hello from server!";
    send(new_socket, msg, strlen(msg), 0);
    printf("Hello message sent.\n");

    // delay between "hello" and file data 
    sleep(1);

    //open a file 
    fp = fopen("/mnt/d/c program/CNT/send.txt", "rb");
    if (fp == NULL) {
        perror("File open error");
        close(new_socket);
        close(server_fd);
        exit(1);
    }
    printf("Sending file...\n");

    // send chunk over the TCP connection
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        send(new_socket, buffer, bytesRead, 0);
    }
    fclose(fp);
    printf("File sent successfully.\n");

    // Close 
    close(new_socket);
    close(server_fd);
    return 0;
}
