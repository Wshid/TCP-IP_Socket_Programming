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
        
        /* 상단의 네줄에는 'read, write 함수가 호출될때마다 문자열 단위로 실제 입출력이 이루어짐'
            이라는 잘못된 가정이 존재
            
            1. TCP는 데이터의 경계가 존재하지 않음
                -> 두번에 write호출을 받아 한번에 전송되는 경우도 생김
            2. 문자열이 길면 두 패킷에 나눠서 보냄
                -> 모든 조각이 clnt에게 전송되지 않았더라도, 클라이언트는 read 호출할 수도 있음
            
            송수신 데이터가 작고, 근거리의 컴퓨터이기 때문에 오류가 발생하지 않았을뿐,
                오류의 가능성은 존재한다.*/
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