#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>

void error_handling(char* message);

int main(int argc, char** argv)
{
    int sock;
    int snd_buf, rcv_buf, state;
    socklen_t len;
    
    sock=socket(PF_INET, SOCK_STREAM, 0);
    if(sock==-1)
        error_handling("socket() error");

    len=sizeof(snd_buf);
    
    state=getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
    if(state==-1) // !state가 아님
        error_handling("getsockopt() error");

   
    len=sizeof(rcv_buf);
    state=getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);
    
    if(state)
        error_handling("getsockopt() error");
    
    printf("Input Buffer size : %d\n", rcv_buf);
    printf("Output Buffer size : %d\n", snd_buf);
    return 0;
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/*
 * 요구대로 정확히 buf size가 결정되지 않음
 *	-> 말 그대로 요구사항만 전달한 것
 * Flow Control과 Error Correction을 위해 최소한의 버퍼 사이즈를 내부적으로 정하고 이행함
*/