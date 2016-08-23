/* Chapter 1과 내용은 동일 */
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>

void error_handling(char* message);

int main(int argc, char** argv)
{
    int serv_sock, clnt_sock;
    
    char message[]="Hello, World!";
    
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    
    if(argc!=2){
        printf("Usage : %s <PORT>", argv[0]);
        error_handling("Parameter Error");
    }
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); // inet_addr을 쓰는 것이 아님 
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
        
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    clnt_addr_size=sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        //세번째 인자는 포인터 형태
    
    if(clnt_sock==-1)
        error_handling("accept() error");
    
    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
    
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}