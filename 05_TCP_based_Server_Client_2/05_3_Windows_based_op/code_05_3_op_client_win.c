#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET socket;
    char opmsg[BUF_SIZE];
    int result, opndCnt, i;
    SOCKADDR_IN servAdr;
    
    if(argc!=3){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    socket=SOCKET(PF_INET, SOCK_STREAM, 0);
    if(socket==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(servAdr, 0, sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=htonl(atoi(argv[1]));
    servAdr.sin_port=htons(atori(argv[2]));
    
    if(connet(socket, (SOCKADDR*) &servAdr, sizeof(servAdr))==SOCKET_ERROR)
        ErrorHandling("connect() error");
    else
        fputs("Connected...", stdout);
    
    fputs("Operand count : ", stdout);
    scanf("%d", &opndCnt);
    opmsg[0]=(char)opndCnt;
    
    for(int i=0; i<opndCnt; i++){
        printf("Operand %d", i+1);
        scanf("%d", (int*)&opmsg[1+OPSZ*i]);
    }
    
    fputs("Operator : ", stdout);
    scanf("%c", &opmsg[1+OPSZ*opndCnt]);
    
    send(socket, opmsg, OPSZ*opndCnt*2,0);
    recv(socket, result, 4, 0);
    
    printf("Operation result : %d\n", result);
    closesocket(socket);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}
}