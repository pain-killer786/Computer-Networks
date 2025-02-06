#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    // Creating socket file descriptor
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket Creation Failed!");
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    printf("Connected!\n");
    // take data from the user
    int n;
    printf("Please enter the size of Dataword: ");
    scanf("%d",&n);
    int* arr;
    arr=(int*)calloc(n,sizeof(int));
    printf("Please enter the %d size Dataword: ",n);
    for (int i=0;i<n;i++)
    {
        
    }
    // send data
    sendto(sockfd,&n,sizeof(int),MSG_CONFIRM,(const struct sockaddr*)&servaddr,sizeof(servaddr));
    sendto(sockfd,arr,n*sizeof(int),MSG_CONFIRM,(const struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("Data sent...\n");
    printf("Waiting for server...\n");
    // receive data
    int size,len;
    recvfrom(sockfd,&size,sizeof(int),MSG_WAITALL,(struct sockaddr*)&servaddr,&len);
    int* receivedBits;
    receivedBits=(int*)calloc(size,sizeof(int));
    recvfrom(sockfd,receivedBits,size*sizeof(int),MSG_WAITALL,(struct sockaddr *)&servaddr,&len);
    printf("Data Received...\n");
    
    // display received data
    for(int i=0;i<size;i++)
    {
    printf("%d ",receivedBits[i]);
    }
    printf("\n");
    close(sockfd);
    return 0;
}
