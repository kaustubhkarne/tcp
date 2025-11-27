#include <stdio.h>
#include <stdlib.h>  // exit
#include <string.h>
#include <unistd.h>   // For close()
#include <arpa/inet.h>     // For sockaddr_in, htons,
#include <math.h>   // sin(), cos(), tan() and M_PI

#define PORT 8080
#define BUF_SIZE 1024

// convert degrees to radians
double deg_to_rad(double deg) {
    return deg * M_PI / 180.0;
}

int main() {
    int sockfd;
    char buffer[BUF_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // clear server and client address structures
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // set server details: IPv4, any local IP, given port
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket to the given IP and port
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    while (1) {
        // receive message from client
        int n = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';

        printf("Received: %s\n", buffer);

        // simple hello check
        if (strcasecmp(buffer, "Hello") == 0) {
            char *reply = "Hello from server!";
            sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *)&cliaddr, len);
        }
        else {
            // Parse trig command: e.g. "sin 30"
            char cmd[10];
            double value;
            if (sscanf(buffer, "%s %lf", cmd, &value) == 2) {
                double result;
                // choose function based on command
                if (strcasecmp(cmd, "sin") == 0) {
                    result = sin(deg_to_rad(value));
                } else if (strcasecmp(cmd, "cos") == 0) {
                    result = cos(deg_to_rad(value));
                } else if (strcasecmp(cmd, "tan") == 0) {
                    result = tan(deg_to_rad(value));
                } else {
                    // unknown operation
                    snprintf(buffer, sizeof(buffer), "Unknown command");
                    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
                    continue;
                }
                // send result back to client
                snprintf(buffer, sizeof(buffer), "%.6lf", result);
                sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
            } else {
                // invalid format message
                char *msg = "Invalid format. Use: sin <angle>";
                sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, len);
            }
        }
    }

    // close socket (never reached in this infinite loop)
    close(sockfd);
    return 0;
}
