#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t id=waitpid(-1, &status, WNOHANG);
    if(WIFEXITED(status)){
        printf("Removed proc id : %d \n", id);
        printf("Child send : %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char** argv)
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGCHLD, &act, 0); // 시그널 등록 과정
    
    pid=fork();
    
    if(pid==0){
        puts("Hi! I'm child process");
        sleep(10);
        return 12;
    } else{
        printf("Child proc id : %d \n", pid);
        pid=fork();
        if(pid==0){
            puts("Hi! I'm child Process");
            sleep(10);
            exit(24);
        } else{
            int i;
            printf("Child proc id : %d \n", pid);
            for(i=0;i<5;i++){
                puts("wait...");
                sleep(5);
            }
        }
    }
    return 0;
}