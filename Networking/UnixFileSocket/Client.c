#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int sockfd;
    int len,i;
    struct sockaddr_un address;
    int result;
    sockfd=socket(AF_UNIX,SOCK_STREAM,0);
    address.sun_family=AF_UNIX;
    strcpy(address.sun_path,"server_socket");
    len=sizeof(address);
    result=connect(sockfd,(struct sockaddr*)&address,len);
    if(result==-1)
    {
        perror("oops:client1");
        exit(1);
    }
    int n;
    printf("Enter the value of n:");
    scanf("%d",&n);
    printf("Enter the array values:");
    int arr[n+1];
    arr[0]=n;
    for(i=1;i<=n;i++)
        scanf("%d",&arr[i]);
    len=sizeof(arr);
    write(sockfd,arr,len);
    read(sockfd,arr,len);
    printf("The sorted array:\n");
    for(i=1;i<=arr[0];i++)
        printf("%d\n",arr[i]);
    printf("\n");
    close(sockfd);
    exit(0);
}
