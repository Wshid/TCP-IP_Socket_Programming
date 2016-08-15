#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/socket.h>

int main(void)
{
    int fd1, fd2, fd3;
    fd1=socket(PF_INET, SOCK_STREAM, 0);
    fd2=open("test.dat", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    fd3=socket(PF_INET, SOCK_STREAM, 0); // 하나의 파일과 두개의 소캣생성, fd를 공유하는 것을 알 수 있다
    
    printf("file descriptor 1 : %d\n", fd1);
    printf("file descriptor 2 : %d\n", fd2);
    printf("file descriptor 3 : %d\n", fd3);
    
    close(fd1); close(fd2); close(fd3);
    return 0;
}