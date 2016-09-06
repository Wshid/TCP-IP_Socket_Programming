#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    socklen_t serv_addr_size;
    char message[BUF_SIZE];
    int str_len;
    
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
    
    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    while(1){
        fputs("Insert Message(q to quit) : ", stdout);
        fgets(message, sizeof(message), stdin); // 사용법 익혀두기
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        //sendto(sock, message, sizeof(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        write(sock, message, sizeof(message));
        
        serv_addr_size=sizeof(serv_addr);
        //str_len=recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&serv_addr, &serv_addr_size);
        str_len=read(sock, message, sizeof(message)-1);
        
        message[str_len]=0;
        fprintf(stdout, "Message from server : %s", message);
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