#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

void ErrorHandling(char* message);
int calculate(int opnd_Cnt, int arr[], char oprator);

int main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET hServsock, hClntsock;
    SOCKADDR_IN servAdr, clntAdr;
    char opmsg[BUF_SIZE];
    int opnd_Cnt, recv_Len, recv_Cnt;
    int clnt_addr_size;
    int result;
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port>", argv[0]);
        exit(1);
    }
    
    if(WSAStartup(MAKEWORD(2,2), &wsaData)!=0)
        ErrorHandling("WSAStartup() error");
    
    
    socket=SOCKET(PF_INET, SOCK_STREAM, 0);
    if(socket==INVALID_SOKCET)
        ErrorHandling("socket() error");

    
    memset(servAdr, 0, sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAdr.sin_port=htons(atoi(argv[1]));
    
    if(bind(hServsock, (SOCKADDR*)&servAdr, sizeof(servAdr)==SOCKET_ERROR)
        ErrorHandling("bind() error");
    
    if(listen(hServsock, 5)==SOCKET_ERROR)
        ErrorHandling("listen() error");
    
    clnt_addr_size=sizeof(clntAdr);
    
    for(int i=0; i<5; i++){
        hClntsock=accept(hServsock, (SOCKADDR*)&clnt_addr, &clnt_addr_size);
        if(hClntsock==INVALID_SOKCET)
            ErrorHandling("accept() error");
        else
            fprintf(stdout, "Connected client : %d",i+1);
        
        recv(hClntsock, &opnd_Cnt, 1,0);
        
        recv_Len=0;
        while(recv_Len < (OPSZ*opnd_Cnt+1)){
            recv_Cnt=recv(hClntsock, &opinfo[recvLen], BUF_SIZE-1); //버퍼 넣는 부분 잘 보기
            recv_Len+=recv_Cnt;
        }
        
        result=calculate(opnd_Cnt, (int*)opmsg, opmsg[recvLen-1]); // 으음..
        
        send(hClntsock, (char*)&result, RLT_SIZE, 0); //문자열 형태로 보내야 하는듯
        
        closesocket(hClntsock);
        
    }
    closesocket(hServsock);
    WSACleanup();
    return 0;
}

int calculate(int opnd_Cnt, int arr[], char oprator)
{
    int ret=0;
    for(int i=0; i<opnd_Cnt, i++){
        switch(oprator){
            case : '+'
                ret+=arr[i];
                break;
            case : '-'
                ret+=arr[i];
                break;
            case : '*'
                ret+=arr[i];
                break;
            default:
                break;
        }
    }
    return ret;
}