#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define BUF_SIZE 30

void error_handling(char* message);
void read_routine(int sock, char* buf);
void write_routine(int sock, char* buf);

int main(int argc, char** argv)
{
    int sock;
    pid_t pid;
    char buf[BUF_SIZE];
    struct sockaddr_in serv_addr;
    if(argc!=3){
        fprintf(stdout, "Usage : %s <ip> <port> \n",argv[1]);
        exit(1);
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    pid=fork();
    if(pid==0)
        write_routine(sock, buf);
    else
        read_routine(sock, buf);
    
    close(sock);
    return 0;
}

void read_routine(int sock, char* buf)
{
    while(1){
        int str_len=read(sock, buf, BUF_SIZE);
        if(str_len==0)
            return;
        
        buf[str_len]=0;
        printf("Message from server : %s", buf);
    }
}

void write_routine(int sock, char* buf)
{
    while(1){
       // fputs("Input Message(q to quit) : ", stdout);
        // ps가 동시에 실행되기때문에 이 구문을 넣게되면 동시에 뜬다
        // buf가 비워지지 않아서 생기는 문제가 아님
        fgets(buf, BUF_SIZE, stdin);
        if(!strcmp(buf, "q\n") || !strcmp(buf, "Q\n")){
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf)); // sizeof라고 하면 당연히 BUF_SIZE가 리턴되므로, str_len을 사용해야 한다.
    }
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}