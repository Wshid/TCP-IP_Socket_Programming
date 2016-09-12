#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    int read_cnt;
    char buf[BUF_SIZE];
    FILE* fp;
    
    if(argc!=3){
        fprintf(stdout, "Usage : %s <ip> <port>", argv[0]);
        exit(1);
    }
    
    fp=fopen("out_07_1_recieve.dat", "wb");
    
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("connect() error");
    
    while((read_cnt=read(sock, buf, BUF_SIZE))!=0) // sock에서 데이터를 읽는다
        fwrite((void*)buf, 1, read_cnt, fp); // 읽은 수만큼 fp에 쓴다
    
    fputs("Received file data", stdout);
    write(sock, "Thank you", 10);
    fclose(fp);
    close(sock);
    return 0;
    
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}