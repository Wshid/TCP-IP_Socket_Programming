#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void error_handling(char* message);

#define BUF_SIZE 30

int main(int argc, char** argv)
{
    int sock;
    socklen_t str_len;
    struct sockaddr_in serv_addr;
    char message[30];
    
    if(argc!=3){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    while(1){
        fputs("Please input message(q to quit) : ", stdout);
        fgets(message, BUF_SIZE, stdin);
        // fgets()의 경우 입력값에 개행문자를 포함시킨다
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        write(sock, message, strlen(message)); // 메세지를 그냥 보낸다. (개행문자 포함)
        str_len=read(sock, message, BUF_SIZE+1); // 읽을때는 BUF_SIZE보다 더 읽은 뒤에
        message[str_len]=0; // 마지막에 NULL 포인터를 삽입한다
        printf("Message from server : %s", message);
    }
    close(sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}