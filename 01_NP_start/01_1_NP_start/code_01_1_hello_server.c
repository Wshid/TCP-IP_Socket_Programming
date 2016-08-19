#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char *message);

int main(int argc, char** argv)
{
    int serv_sock;
    int clnt_sock;
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    
    char message[]="Hello World!";
    
    if(argc!=2)
    {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); //소켓 생성 // SOCK_STREAM = IP
    if(serv_sock==-1)
        error_handling("Socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // INADDR_ANY : 현재 컴퓨터의 IP 지정
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1) // IP:PORT 할당
        error_handling("bind() error");
    
    if(listen(serv_sock, 5)==-1) // 소켓의 개방, 연결요청 수락할 수 있는 상태로 변경
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); //연결요청 수락, 오기전까지는 대기
    if(clnt_sock==-1)
        error_handling("accept() error");
        
    write(clnt_sock, message, sizeof(message)); // 데이터 전송하는 기능, accept이후이기때문에 연결요청을 미리 받았음을 의미
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}