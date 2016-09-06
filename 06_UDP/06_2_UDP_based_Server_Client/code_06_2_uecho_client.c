#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char* message);

int main(int argc, char** argv)
{
    int clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    char message[BUF_SIZE];
    socklen_t addr_sz;
    int str_len;
    
    
    if(argc!=3){
        fprintf(stdout, "Usage : %s <ip> <port>\n",argv[0]);
        exit(1);
    }
    
    clnt_sock=socket(PF_INET, SOCK_DGRAM, 0);
    if(clnt_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    
    while(1){
        fputs("Insert message(q to quit) : ",stdout);
        fgets(message, sizeof(message), stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        //sendto 함수 호출시 임의의 IP와 PORT가 할당된다.
        sendto(clnt_sock, message, strlen(message), 0,
                (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        addr_sz=sizeof(clnt_addr);
        
        str_len=recvfrom(clnt_sock, message, BUF_SIZE, 0,
                        (struct sockaddr*)&clnt_addr, &addr_sz);
        message[str_len]=0;
        fprintf(stdout, "Message from server : %s\n",message);
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