/*
 * 둘 이상의 clnt에게 동시에 서비스를 제공하는 에코서버 만들기

 * clnt의 요청이 있을 때마다
 *   에코서버는 child.ps를 생성해서 서비스를 제공한다
 *       clnt가 5명, 자식 ps가 5개
    
 *   1. e_serv, accept로 연결 요청 수락
 *   2. 이때 얻게되는 fd를 child ps를 통해 넘겨준다
 *   3. child ps는 전달받은 fd를 기준, 서비스를 제공한다
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void error_handling(char* message);
void read_childproc(int sig);

int main(int argc, char** argv)
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    int clnt_addr_size, str_len;
    char buf[BUF_SIZE];
    
    pid_t pid;
    struct sigaction act;
    
    if(argc!=2){
        fprintf(stdout, "Usage : %s <port> \n", argv[1]);
        exit(1);
    }
    
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGCHLD, &act, 0);
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htons(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    while(1)
    {
        clnt_addr_size=sizeof(clnt_addr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock==-1)
            continue;
        else
            puts("new client connected...");
        
        pid=fork(); // clnt_sock의 fd를 자식과 부모 둘이 갖는다
        if(pid==-1){
            close(clnt_sock);
            continue; // error_handling을 이용하여 종료시키면 서비스 제공이 불가함
        }
        if(pid==0){ /* child ps 실행 영역 */
            close(serv_sock); // 서버 소켓을 닫는다. child.ps로 serv_sock의 fd도 복사되었기 때문
            while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0)
                write(clnt_sock, buf, str_len);
            
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }
        else
            close(clnt_sock); // accept로 만들어진 clnt_sock을 자식 ps가 가졌으므로, 부모 ps는 지운다
    }
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid=waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status))
        printf("removed proc id : %d\n", pid);
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}