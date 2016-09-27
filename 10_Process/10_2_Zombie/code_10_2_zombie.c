#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char** argv)
{
    pid_t pid=fork();
    
    if(pid==0)
        puts("Hi, I am a child process");
    else{
        printf("Child Process ID : %d\n", pid);
        sleep(30); // 좀비 상태를 확인하기 위해 pps의 종료시점을 늦춘다
    }
    
    if(pid==0)
        puts("End child process");
    else
        puts("End parent process");
    return 0;
}