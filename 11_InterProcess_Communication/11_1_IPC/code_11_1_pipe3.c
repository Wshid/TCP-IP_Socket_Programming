#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define BUF_SIZE 30

int main(int argc, char** argv)
{
    int fds1[2], fds2[2];
    char str1[]="Who are you?";
    char str2[]="Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;
    
    pipe(fds1), pipe(fds2); // 파이프를 두개 생성한다
    pid=fork(); //자식프로세스를 생성
    if(pid==0){ // child.ps가 사용하는것, fds1[1], fds2[0]
        write(fds1[1], str1, sizeof(str1));
        read(fds2[0], buf, BUF_SIZE);
        printf("Child proc output : %s \n", buf);
    } else{ //pps가 사용하는것, fds1[0], fds2[1]
        read(fds1[0], buf, BUF_SIZE);
        printf("Parent proc output : %s \n", buf);
        write(fds2[1], str2, sizeof(str2));
        sleep(3); // 단순히 pps 지연시키기 위함. 큰 의미는 없음
    }
    return 0;
}