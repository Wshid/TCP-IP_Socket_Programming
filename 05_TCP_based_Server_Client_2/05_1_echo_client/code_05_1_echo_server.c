#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr, clnt_addr;
    int serv_sock, clnt_sock;
    int str_len;
    int clnt_addr_size;
    char message[BUF_SIZE];
    
    if(argc!=2){
        printf("Usage : %s <port>\n",argv[0]);
        exit(1);
    }
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind error");
    
    if(listen(serv_sock, 5)==-1)
        error_handling("listen error");
    
    clnt_addr_size=sizeof(clnt_addr);
    
    for(int i=0;i<5;i++){
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock==-1)
            error_handling("accept error");
        else
            printf("Connect client %d\n", i+1);
        
        while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
            write(clnt_sock, message, str_len);
    }
    
    close(clnt_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}