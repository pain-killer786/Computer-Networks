#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len,client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    unlink("server_socket");
    server_sockfd=socket(AF_UNIX,SOCK_STREAM,0);
    server_address.sun_family=AF_UNIX;
    strcpy(server_address.sun_path,"server_socket");
    server_len=sizeof(server_address);
    bind(server_sockfd,(struct sockaddr*)&server_address,server_len);
    listen(server_sockfd,5);
    while(1)
    {
        int arr[50];
        printf("server waiting\n");
        client_len=sizeof(client_address);
        client_sockfd=accept(server_sockfd,(struct sockaddr*)&client_address,&client_len);
        read(client_sockfd,arr,sizeof(arr));
        for(int i=1;i<arr[0];i++)
        {
            int pos=i;
            for(int j=i+1;j<=arr[0];j++)
            {
                if(arr[j]<arr[pos])
                    pos=j;
            }
            int temp=arr[pos];
            arr[pos]=arr[i];
            arr[i]=temp;
        }
        printf("The sorted array is:\n");
        for(int i=1;i<=arr[0];i++)
            printf("%d\n",arr[i]);
        printf("\n");
        write(client_sockfd,arr,sizeof(arr));
    }
    close(client_sockfd);
}