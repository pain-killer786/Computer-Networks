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
struct sockaddr_in cl,src;
int cfd;
int main()
{
pthread_t snd,rcv;
cfd=socket(AF_INET,SOCK_DGRAM,0);
cl.sin_family=AF_INET;
inet_aton("127.0.0.1",&(cl.sin_addr)); //Client Address
cl.sin_port=htons(8760); //Client Port
src.sin_family=AF_INET;
inet_aton("127.0.0.1",&(src.sin_addr)); //Server Address
src.sin_port=htons(8760); //Server Port
pthread_create(&snd,NULL,send_thread,NULL);
pthread_create(&rcv,NULL,recv_thread,NULL);
pthread_join(snd,NULL);
pthread_join(rcv,NULL);
close(cfd);
return 0;
}
void *send_thread(void *a)
{
char str[200];
int len;
len=sizeof(struct sockaddr_in);
sendto(cfd,"!S!",3,0,(struct sockaddr *)&src,len);
while(1)
{
fgets(str,200,stdin);
sendto(cfd,str,200,0,(struct sockaddr *)&src,len);
if(strncmp(str,"BYE",3)==0)
exit(0);
}
}
void *recv_thread(void *a)
{
int n;
char str[200];
int len;
len=sizeof(struct sockaddr_in);

while(1) { n=recvfrom(cfd,str,200,0,(struct sockaddr *)&src,&len); str[n]='\0'; if(n>0) { printf("Server: %s",str); fflush(stdout); }if(strncmp(str,"BYE",3)==0) exit(0); } }
