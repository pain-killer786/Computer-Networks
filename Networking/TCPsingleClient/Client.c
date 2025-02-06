#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() 
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER_SIZE] = {0};
    char receivedBuffer[MAX_BUFFER_SIZE * 2] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to server
    if (connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Input bit stream from user
    printf("Enter bit stream: ");
    scanf("%s", buffer);

    // Send bit stream to server
    send(sock, buffer, strlen(buffer), 0);
    printf("Bit stream sent to server\n");

    // Receive modified bit stream from server
    valread = read(sock, receivedBuffer, MAX_BUFFER_SIZE * 2);
    printf("Modified bit stream received from server: %s\n", receivedBuffer);

    return 0;
}
