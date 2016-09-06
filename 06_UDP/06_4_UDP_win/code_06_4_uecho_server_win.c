/*
    #include<winsock2.h>
    
    int sendto(SOCKET s,
                const char* buf,
                int len,
                int flags,
                const struct sockaddr* to,
                int tolen);
            -> 성공시 전송된 바이트 수, 실패시 SOCKET_ERROR 반환
    
    int recvfrom(SOCKET s,
                const char* buf,
                int len,
                int flags,
                struct sockaddr* from,
                int *fromlen);
            -> 성공시 수신한 바이트 수, 실패시 SOCKET_ERROR 반환

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 30

void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET servSock;
    SOCKADDR_IN servAddr, clntAddr;
    char message[BUF_SIZE];
    int strLen;
    int clntAddrSize;
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    servSock=SOCKET(PF_INET, SOCK_DGRAM, 0);
    if(servSock==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[2]));
    
    if(bind(servSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
        ErrorHandling("bind() error");
    
    while(1){
        clntAddrSize=sizeof(clntAddr);
        strLen=recvfrom(servSock, message, BUF_SIZE, 0, (SOCKADDR*)&clntAddr, &clntAddrSize);
        sendto(servSock, message, strLen, 0, (SOCKADDR*)&clntAddr, clntAddrSize);
    }
    closeSocket(servSock);
    WSACleanup();
    return 0;
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}