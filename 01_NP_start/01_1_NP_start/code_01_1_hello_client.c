/*
    주로 클라이언트 프로그램에서는 socket 함수와 connect함수로 이루어짐(소켓 애성 및 연결 요청)
        서버 프로그램보다 상대적으로 간단함
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;
    
    if(argc!=3){
        printf("Usage : %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0); // 소켓을 생성, bind-listen 함수 호출 : server // connect : client
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect error");
    
    str_len=read(sock, message, sizeof(message)-1);
    
    if(str_len==-1)
        error_handling("read error");
    
    printf("Message from server : %s \n", message);
    close(sock);
    return 0;

}