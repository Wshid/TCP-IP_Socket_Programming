#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

void timeout(int sig)
{
    if(sig==SIGALRM)
        puts("Time out!");
    alarm(2);
}

int main(int argc, char** argv)
{
    int i;
    struct sigaction act;
    act.sa_handler=timeout; // 시그널 함수의 등록
    sigemptyset(&act.sa_mask); // sa_mask의 모든 비트 0으로 초기화
    act.sa_flags=0;
    sigaction(SIGALRM, &act, 0);
    
    alarm(2);
    
    for(i=0; i<3; i++){
        puts("wait...");
        sleep(100);
    }
    return 0;
}