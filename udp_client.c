#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // For close(), sleep()
#include <arpa/inet.h>  // sockaddr_in, htons, sendto, recvfrom

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // clear server address structure
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    // server IP (here using INADDR_ANY / local machine)
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    // Send Hello message to server
    char *hello = "Hello";
    sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // receive hello reply
    int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server reply: %s\n", buffer);

    // Trig calculator loop
    while (1) {
        printf("Enter trig command (sin/cos/tan angle in degrees, or end): ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';   // remove newline

        // check for exit condition
        if (strcasecmp(buffer, "end") == 0)
            break;

        // send user command to server
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        // receive result from server
        n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Server reply: %s\n", buffer);
    }

    // close socket
    close(sockfd);
    return 0;
}
