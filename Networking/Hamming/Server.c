#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<math.h>
#define PORT 8080
#define MAXLINE 1024
void hammingCalculation(int data[],int hammingCode[],int size)
{
    int i,p,c,j=0,count=0;
    for(i=0;i<size;i++)
    {
        p=pow(2,i);
        if(p<size)
        {
            hammingCode[size-p]=-1;
        }
        if(hammingCode[i]!=-1)
        {
            hammingCode[i]=data[j];
        j++;
        }
    }
    for(i=size-1;i>=0;i--)
    {
        if(hammingCode[i]==-1)
        {
        j=size-i+1;
        //setting position of j
        while(j<=size)
        {
        if((size-i)&j) //comparing with position of i
        {
        if(hammingCode[size-j]==1) //checking the index position in the array
        count++;
        }
        j++;
        }
        if(count%2!=0)
        hammingCode[i]=1;
        else
        hammingCode[i]=0;
        count=0;
        }
    }
}
int main()
{
int sockfd;
struct sockaddr_in servaddr,cliaddr;
// Creating socket file descriptor
if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
{
perror("Socket Creation Failed!");
exit(0);
}
memset(&servaddr,0,sizeof(servaddr));
memset(&cliaddr,0,sizeof(cliaddr));
// Filling server information
servaddr.sin_family=AF_INET; // IPv4
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(PORT);
// Bind the socket with the server address
if(bind(sockfd,(const struct sockaddr
*)&servaddr,sizeof(servaddr))<0)
{
perror("Binding Failed!");
exit(0);
}
printf("Waiting...\n");
int len;
len=sizeof(cliaddr); //len is value/result
//receive data from client
int size;
recvfrom(sockfd,&size,sizeof(int),MSG_WAITALL,(struct sockaddr
*)&servaddr,&len);
int* receivedBits;
receivedBits=(int*)calloc(size,sizeof(int));
recvfrom(sockfd,receivedBits,size*sizeof(int),MSG_WAITALL,(struct
sockaddr *)&servaddr,&len);
int r;
int* sentBits;
for(r=0;;r++)
{
if(pow(2,r)>=size+r+1)
break;
}int sizeofCode=size+r;
sentBits=(int*)calloc(sizeofCode,sizeof(int));
printf("Data Received...\n");
// perform operation
// call the hamming calculation function
printf("Performing operations...\n");
hammingCalculation(receivedBits,sentBits,sizeofCode);
//send data to client
sendto(sockfd,&sizeofCode,sizeof(int),MSG_CONFIRM,(const struct
sockaddr *)&servaddr,sizeof(servaddr));
sendto(sockfd,sentBits,sizeofCode*sizeof(int),MSG_CONFIRM,(const
struct sockaddr *)&servaddr,sizeof(servaddr));
printf("Data Sent...\n");
return 0;
}
