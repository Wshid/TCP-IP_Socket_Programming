#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(int argc, char** argv)
{
    int status;
    pid_t pid=fork();
    
    if(pid==0){
        sleep(15); // 15초 뒤에 24라는 값을 반환할 예쩡
        return 24;
    }else{
        while(!waitpid(-1, &status, WNOHANG)){ // 해당 시간에 child.ps가 종료 안되어있어도 noblocking 된다
            sleep(3); //3초마다 체크하기 위해서 delay 줌
            puts("sleep 3sec");
        }
        
        if(WIFEXITED(status))
            printf("Child send : %d \n",WEXITSTATUS(status)); // 종료했다면, 그 값을 확인해야함
    }
    
    return 0;
}