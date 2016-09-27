#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in serv_addr, clnt_addr;
    char message[BUF_SIZE];
    int str_len;
    
    if(argc!=3){
        printf("Usage : %s <IP> <PORT>", argv[0]);
        error_handling("Parameter error");
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    else
        puts("Connected........");
    
    while(1){
        fputs("Input Message(Q to quit) : ",stdout);
        fgets(message, BUF_SIZE, stdin);
        
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        write(sock, message, strlen(message));
        str_len=read(sock, message, BUF_SIZE+1);
        message[str_len]=0; // 문자열의 끝을 나타내기 위해 꼭 추가할 것
        printf("Message from server : %s", message);

    }
    
    close(sock);
    return 0;
    
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}