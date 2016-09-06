#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    char msg1[]="Hi";
    char msg2[]="I'm another UDP host";
    char msg3[]="Nice to meet you";
    int sock;
    socklen_t serv_addr_size;
    
    if(argc!=3){
        fprintf(stdout, "Usage : %s <ip> <port>\n",argv[0]);
        exit(1);
    }
    
    sock=socket(PF_INET, SOCK_DGRAM, 0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    sendto(sock, msg1, sizeof(msg1), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg2, sizeof(msg2), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg3, sizeof(msg3), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}