#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 30

void ErrorHandling(char* message);

int main(int argc, char** argv)
{
    SOCKET hServsock, hClntsock;
    WSADATA wsaData;
    FILE *fp;
    char buf[BUF_SIZE];
    int readCnt;
    
    SOCKADDR_IN servAdr, clntAdr;
    int clntAdrSize;
    
    fp=fopen("code_07_1_file_server_win.c", "rb");
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    hServsock=socket(PF_INET, SOCK_STREAM, 0);
    if(socket==INVALID_SOCKET)
        ErrorHandling("socket() error");
    
    memset(&servAdr, 0, sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAdr.sin_port=htons(atoi(argv[1]));
    
    if(bind(hServsock, (SOCKADDR*) &servAdr, sizeof(servAdr))==SOCKET_ERROR)
        ErrorHandling("bind() error");
    
    if(listen(hServsock, 1)==SOCKET_ERROR)
        ErrorHandling("listen() error");
    
    clntAdrSize=sizeof(clntAdr);
    if((hClntsock=accpet(hServsock, (SOCKADDR*) &clntAdr, &clntAdrSize))==INVALID_SOCKET)
        ErrorHandling("accept() error");
        
    while(1){
        readCnt=fread((void*)buf, 1, BUF_SIZE, fp); // 파일에서 사용시 void*로 묶어주어야 함
        if(readCnt<BUF_SIZE){
            send(hClntsock, (char*)&buf, readCnt, 0); //왜 이런방식으로 사용할까..?
            break;
        }
        send(hClntsock, (char*)&buf, BUF_SIZE); // send시에 유의하기 (char*)&
    }
    
    shutdown(hClntsock, SD_SEND);
    recv(hClntsock, (char*)buf, BUF_SIZE, 0); // recv 및 send를 할때 buf를 char 형으로 보내주어야 함
    fprintf(stdout, "Message from client : %s \n", buf);
    
    fclose(fp);
    close(hClntsock);
    close(hServsock);
    WSACleanup();
    return 0;
}

void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}