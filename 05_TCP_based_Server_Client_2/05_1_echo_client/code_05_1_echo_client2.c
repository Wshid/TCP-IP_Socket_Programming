#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char** argv)
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    
    if(argc!=3){
        printf("Usage : %s <ip> <port>",argv[0]);
        exit(1);
    }
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
        perror("connect error");
    else
        puts("Connected...");
    
    while(1){
        fputs("Input Message(Q to quit) : ", stdout);
        fgets(message, BUF_SIZE, stdin); //fgets(stdin에서 BUF_SIZE만큼 message로)
        if(!strcmp(message, "Q\n") || !strcmp(message, "q\n"))
            break;
        
        str_len=write(sock, message, sizeof(message)); // 보내고 나서, 기다려야 하는데..
        
        recv_len=0;
        while(recv_len<str_len){
            recv_cnt=read(sock, &message[recv_len], BUF_SIZE-1); //위치를 위해 message[recv_len], 주소값을 던져주기 위해 &
            if(recv_cnt==-1)
                error_handling("read error");
            recv_len+=recv_cnt;
        }
        message[recv_len]=0;
        printf("message from server : %s", message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}