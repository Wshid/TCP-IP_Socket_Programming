#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 30

void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    SOCKET sock;
    char buf[BUF_SIZE];
    int readCnt;
    WSADATA wsaData;
    SOCKADDR_IN servAdr, clntAdr;
    FILE* fp;
    
    if(argc!=3){
        fprintf(stdout, "Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    
    fp=fopen("out_07_2_recieve_win.dat", "wb");
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(socket==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(&servAdr, 0, sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=inet_addr(argv[1]);
    servAdr.sin_prot=htons(argv[2]);
    
    if(connect(sock, (SOCKADDR*) &servAdr, sizeof(servAdr))==SOCKET_ERROR)
        ErrorHandling("connect() error");
    
    while(readCnt=recv(sock, buf, BUF_SIZE, 0))
        fwrite((void*)buf, 1, readCnt, fp);
    
    fputs("Received file data", stdout);
    send(sock, "Thank you", 10, 0);
    fclose(fp);
    closesocket(sock);
    WSACleanup();
    return 0;
    
}

void ErrorHandling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}