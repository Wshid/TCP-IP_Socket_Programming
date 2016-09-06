#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 30

void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET clntSock;
    SOCKADDR_IN servAddr;
    int servAddrSize; // 사용하지 않는 변수
    int strLen;
    
    if(argc!=3){
        fprintf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    clntSock=SOCKET(PF_INET, SOCK_DGRAM, 0);
    if(clntSock==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(&servAddr, sizeof(servAddr), 0);
    servAddr.sin_family=AF_INET;
    servAddr.sin_addr.s_addr=inet_addr(argv[1]);
    servAddr.sin_port=htons(atoi(argv[2]));
    
    if(connect(clntSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
        ErrorHandling("connect() error");
    
    while(1){
        fputs("Insert Message(q to quit) : ", stdout);
        fgets(message, sizeof(message), stdin);
        
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        servAddrSize=sizeof(servAddr); // 필요 없는 구문
      //  sendto(clntSock, message, sizeof(message), 0, (SOCKADDR*)&servAddr, sizeof(servAddr));
        send(clntSock, message, sizeof(message),0);
        strLen=recv(clntSock, message, sizeof(message)-1,0);
        message[strLen]=0;
        fprintf(stdout, "Message from server : %s ", message);
        
    }
    closeSocket(clntSock);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}