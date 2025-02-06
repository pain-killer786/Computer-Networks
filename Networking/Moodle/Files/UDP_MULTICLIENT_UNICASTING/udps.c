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
void *recv_thread(void *a);
void *send_thread(void *a);
int cfd,sfd;
struct sockaddr_in ser,cl;
int main()
{
pthread_t snd,rcv;
sfd=socket(AF_INET,SOCK_DGRAM,0);
ser.sin_family=AF_INET;
inet_aton("127.0.0.1",&(ser.sin_addr)); //Server Address
ser.sin_port=htons(8760); //Server Port
bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
pthread_create(&snd,NULL,send_thread,NULL);
pthread_create(&rcv,NULL,recv_thread,NULL);
pthread_join(snd,NULL);
pthread_join(rcv,NULL);
close(cfd);
return 0;
}
void *send_thread(void *a)
{
int n,len;
len=sizeof(struct sockaddr_in);
char str[200];
while(1)
{
fgets(str,200,stdin);
sendto(sfd,str,200,0,(struct sockaddr *)&cl,len);
if(strncmp(str,"BYE",3)==0)
exit(0);
}
}
void *recv_thread(void *a)
{
int n,len;
len=sizeof(struct sockaddr_in);
char str[200];
while(1)
{
n=recvfrom(sfd,str,200,0,(struct sockaddr *)&cl,&len);
str[n]='\0';
if((n>0)&&(strncmp(str,"!S!",3)))
{
printf("Client : %s",str);
fflush(stdout);
}
if(strncmp(str,"BYE",3)==0)

exit(0);
}
}
