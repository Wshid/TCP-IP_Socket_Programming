/* 하나의 파이프를 통해 두 ps가 양방향으로도 주고 받을 수 있음 */

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define BUF_SIZE 30

int main(int argc, char** argv)
{
    int fds[2];
    char str1[]="Who are you?";
    char str2[]="Thank you for your message";
    char buf[BUF_SIZE];
    pid_t pid;
    
    pipe(fds);
    pid=fork();
    
    if(pid==0){ // child.ps일 때, str1의 내용을 보내고, fds[0]에 있는 값을 가져온다
        write(fds[1], str1, sizeof(str1));
        sleep(2); // 시간차를 두기 위해 사용한다.
        read(fds[0], buf, BUF_SIZE);
        printf("Child proc output : %s \n", buf);
    } else{
        read(fds[0], buf, BUF_SIZE); // parent일 때, 먼저 데이터를 수신한뒤, 
        printf("Parent proc output : %s \n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }
}

/* 파이프에 데이터가 전달 되었을때, 먼저 가져가는 ps에게 데이터가 전달됨 */