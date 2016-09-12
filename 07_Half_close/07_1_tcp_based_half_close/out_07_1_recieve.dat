#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define BUF_SIZE 30

void error_handling(char* message);

int main(int argc, char** argv)
{
    int serv_sock, clnt_sock;
    socklen_t clnt_addr_size;
    struct sockaddr_in serv_addr, clnt_addr;
    char buf[BUF_SIZE];
    int read_len, read_cnt;
    FILE* fp;
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    fp=fopen("code_07_1_file_server.c", "rb");
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);
    
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    
    while(1){
        read_cnt=fread((void*)buf, 1, BUF_SIZE, fp); // file에서 buf로 읽기
        if(read_cnt<BUF_SIZE){ //BUF_SIZE보다 읽은 수가 적다면 -> 파일의 끝이 보인다면
            write(clnt_sock, buf, read_cnt); // socket에 읽은 데이터를 보내주기
            break;
        }
        write(clnt_sock, buf, BUF_SIZE);
    }
    
    shutdown(clnt_sock, SHUT_WR);
    read(clnt_sock, buf, BUF_SIZE);
    fprintf(stdout, "Message from client : %s \n", buf);
    
    fclose(fp);
    close(clnt_sock);
    close(serv_sock);
    return 0;
    
}

void error_handling(char* message)
{
    fputs(message, stdout);
    fputc('\n', stdout);
    exit(1);
}