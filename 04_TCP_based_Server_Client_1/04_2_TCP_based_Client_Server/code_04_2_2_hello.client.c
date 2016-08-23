#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

void error_handling(char* message);

int main(int argc, char** argv)
{
    int sock, str_len;
    struct sockaddr_in serv_addr;
    
    char message[30];
    
    if(argc!=3){
        printf("Usage : %s <IP> <PORT>", argv[0]);
        error_handling("parameter error");
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1) error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
        error_handling("connect error");
    
    str_len=read(sock, message, sizeof(message));
    
    printf("Message from server : %s \n", message);
    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}