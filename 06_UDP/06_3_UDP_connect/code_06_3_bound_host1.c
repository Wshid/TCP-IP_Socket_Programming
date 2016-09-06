/* server의 역할을 하는 bound_host
 * 5초 간격으로 3번 받는다.
 */

#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr, clnt_addr;
    char message[BUF_SIZE];
    int serv_sock;
    int clnt_addr_size;
    int str_len;
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    
    serv_sock=socket(PF_INET, SOCK_DGRAM, 0);
    if(serv_sock==-1)
        error_handling("socket()");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind()");
    
    for(int i=0; i<3; i++){ // 5초 간격으로 받아낸다.
        sleep(5); // delay 5 sec
        clnt_addr_size=sizeof(clnt_addr);
        str_len=recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        
        fprintf(stdout, "Message %d : %s \n",i+1,message);
    }
    close(serv_sock);
    return 0;
}  

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}