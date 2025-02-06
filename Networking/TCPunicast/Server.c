
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
#include<termios.h>
#include<stdlib.h>

struct sockaddr_in ser,cli;
void *recv_thread(void *arg);
void *send_thread(void *arg);
pthread_t sample_t;
int sfd,cfd,temp=0;

int main()
{
    int len,num;
    pthread_t snd,rcv;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ser.sin_family=AF_INET;
    inet_aton("10.10.99.90",&(ser.sin_addr));
    ser.sin_port=htons(8760);
    num=bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
    printf("Chatroom Ready!\n");
    num=listen(sfd,1);
    len=sizeof(cli);
    cfd=accept(sfd,(struct sockaddr*)&cli,&len);
    printf("Client Joined!\n");
    pthread_create(&snd,NULL,send_thread,NULL);
    pthread_create(&rcv,NULL,recv_thread,NULL);
    pthread_join(snd,NULL);
    return 0;
}

void *send_thread(void *arg)
{
    char str[200];
    while(1)
    {
        fgets(str,200,stdin);
        if(strcmp(str,"!DISCONNECT")==10)
        {
            pthread_cancel(sample_t);
            close(sfd);
            exit(0);
        }
        else
        {
            write(cfd,(void *)str,sizeof(str));
        }
    }
}

void *recv_thread(void *arg)
{
    int n;
    char str[200];
    sample_t=pthread_self();
    while(1)
    {
        n=read(cfd,(void *)str,sizeof(str));
        if(n>0)
        {
            if(strcmp(str,"!DISCONNECT")==10)
            {
                printf("Client Left!\n");
            }
            else
            {
                printf("Client : %s",str);
            }
            fflush(stdout);
        }
    }
}