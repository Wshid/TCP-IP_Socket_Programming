#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

void error_handling(char* message);

int main(void){
    int fd;
    char buf[]="Let's go!\n";
    
    fd=open("out_01_2_low_open.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664); // 저장되지 않은 새로운 파일 생성
    if(fd==-1)
        error_handling("open() error");
    printf("file descriptor : %d", fd);
    
    if(write(fd, buf, sizeof(buf))==-1) // buf의 내용을 fd에 기록
        error_handling("write() error");
    close(fd);
    return 0;
}
void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}