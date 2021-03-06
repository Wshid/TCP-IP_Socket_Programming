#include<stdlib.h>
#include<stdio.h>
#include<winsock2.h>
void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET hServSock, hClntSock;
    SOCKADDR_IN servAddr, clntAddr; //리눅스와는 별개로 hServSock과 servAddr이 구분
    
    int szClntAddr;
    char message[]="Hello World!";
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0) //socket lib. 초기화
        ErrorHandling("WSAStartup() error!");
    
    hServSock=socket(PF_INET, SOCK_STREAM, 0);
    if(hServSock==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family=AF_INET; // PF_INET과 같은 의미, ipv4 // 프로토콜 체계 // 주소 체계
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port=htons(atoi(argv[1]));
    
    if(bind(hServSock, (SOCKADDR*) &servAddr, sizeof(servAddr))==SOCKET_ERROR)
        ErrorHandling("bind() error");
    
    if(listen(hServSock, 5)==SOCKET_ERROR) // linux와 동일
        ErrorHandling("listen() error");
        
    szClntAddr=sizeof(clntAddr);
    hClntSock=accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
    if(hClntSock==INVALID_SOCKET)
        ErrorHandling("accept() error");
        
    send(hClntSock, message, sizeof(message),0);
    closesocket(hClntSock);
    closesocket(hServSock);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}