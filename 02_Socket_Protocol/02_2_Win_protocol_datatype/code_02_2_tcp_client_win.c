/*
#include<winsock2.h>

SOCKET socekt(int af, int type, int protocol);
    -> 성공시 소켓 핸들, 실패시 INVALID_SOCKET(-1)

SOCKET(int형) = 정수로 표현되는 소켓의 핸들값 저장

SOCKET soc=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
if(soc==INVALID_SOCKET)
    errorHandling("...");
    
    hello_server_win.c -> tcp_server_win.c // 변경 x
    hello_client_win.c -> tcp_client_win.c // read 변경

*/

#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET hsocket;
    SOCKADDR_IN servAddr;
    
    char message[30];
    int strLen=0;
    int idx=0, readLen=0;
    
    if(argc!=3){
        printf("Usage : %s <IP> <PORT>\n",argv[0]);
        exit(1);
    }
    
    if(WSAstartup(MAKEWORD(2,2), &wsaData)!=0)
        error_handling("WSAstartup() error!");
    
    hsocket=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(hsocket==INVALID_SOCKET)
        error_handling("socket() error!");
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));
    
    if(connect(hsocket, (SOCKADDR*) servAddr, sizeof(servAddr))==SOCKET_ERROR)
        error_handling("connect() error!");
    
    while(readLen=recv(hsocket, &message[idx++],1,0)){
        if(readLen==-1)
            error_handling("read() error");
    }
    
    printf("Message from server : %s \n", message);
    printf("Function read call count : %d \n", strLen);
    
    closesocket(hsocket);
    WSACleanup();
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}