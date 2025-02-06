#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

// Function to perform bit stuffing
void performBitStuffing(char *input, char *output) 
{
    int count = 0;
    for (int i = 0; input[i] != '\0'; i++) 
    {
        output[count++] = input[i];
        if (input[i] == '1') 
        {
            output[count++] = '0';
        }
    }
    output[count] = '\0';
}

int main() 
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};
    char stuffedBuffer[MAX_BUFFER_SIZE * 2] = {0};

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Prepare sockaddr_in structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept connection from client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Read bit stream from client
    valread = read(new_socket, buffer, MAX_BUFFER_SIZE);
    printf("Received bit stream from client: %s\n", buffer);

    // Perform bit stuffing
    performBitStuffing(buffer, stuffedBuffer);

    // Send stuffed bit stream back to client
    send(new_socket, stuffedBuffer, strlen(stuffedBuffer), 0);
    printf("Stuffed bit stream sent to client\n");

    return 0;
}
