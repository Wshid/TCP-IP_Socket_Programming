#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define BUF_SIZE 30

int main(int argc, char** argv)
{
    int fds[2];
    char str[]="Who are you?";
    char buf[BUF_SIZE];
    pid_t pid;
    
    pipe(fds); // 이와 같이 사용함, 초기화 되지 않았지만 공간을 지정함
    pid=fork();
    
    if(pid==0) //자식프로세스에서 입구를 맡는다. 목적은 child.ps -> pps
    {
        write(fds[1], str, sizeof(str)); // str의 내용을 fds에 작성
    }else {
        read(fds[0], buf, BUF_SIZE); // 출구에 있는 내용을 buf에 작성
        puts(buf);
    }   // 실상 str -> buf가 된다.
    
    return 0;
}