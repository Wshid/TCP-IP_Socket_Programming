/* serv는 clnt가 전송하는 문자열을 전달되는 순서대로 파일에 저장한다
 * 별도의 ps가 담당하도록 함, 데이터 수신과정에서 pipe가 필요함
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/types.h>

#define BUF_SIZE 100

void error_handling(char* message);
void read_childproc(int sig);

int main(int argc, char** argv)
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int fds[2];
    pid_t pid;
    int state, str_len;
    char buf[BUF_SIZE];
    
    struct sigaction act;
    
    if(argc!=2){
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }
    
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD, &act, 0);
    
    serv_sock=socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock==-1)
        error_handling("socket() error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));
    
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
        error_handling("bind() error");
    
    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");
    
    pipe(fds); // 파일의 데이터 저장을 담당하는 ps를 만든다
    pid=fork(); // pps의 경우엔 그냥 넘어간다
    
    if(pid==0){ // child.ps라면.. 파이프로 파일을 받아 작성하는 역할을 함
        FILE* fp=fopen("out_11_2_echomsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        int i, len;
        
        for(i=0; i<10; i++){
            len=read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void*)msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }
    
    while(1){
        clnt_addr_size=sizeof(clnt_addr);
        clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock==-1)
            continue;
        else
            puts("new client connected...");
        
        pid=fork();
        if(pid==0){ // child.ps에서는 데이터를 받아서 각각 clnt와 fds로 쓴다
            close(serv_sock); // serv_sock은 필요 없으니 제거
            while((str_len=read(clnt_sock, buf, BUF_SIZE))!=0){
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }
            close(clnt_sock); // 할일 다했으면 종료
            puts("clientt disconnected....");
            return 0;
        }else
            close(clnt_sock); // pps일 경우 clnt_sock만 닫고 끝낸다. serv_sock은 계속 유지시켜야 하므로
    }
    
    close(serv_sock);
    return 0;
}

void read_childproc(int sig)
{
    pid_t pid;
    int status;
    pid=waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(pid))
        printf("removed proc id : %d \n", pid);
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}