/*
inet_aton : 기능상으로는 inet_addr과 동일
    문자열 주소 -> 32비트 정수, 네트워크 바이트 순서로 정렬
    단, in_addr 구조체 사용
    
    int inet_aton(const char *string, struct in_addr *addr);
        // string : IP주소 담고 있는 문자열
        // addr : 변환된 정보 저장, in_addr
*/

#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>

void error_handling(char* message);

int main(int argc, char** argv)
{
    char* addr="127.232.124.79";
    struct sockaddr_in addr_inet;
    
    if(!inet_aton(addr, &addr_inet.sin_addr))
        error_handling("Conversion error!");
    else
        printf("Network ordered integer addr : %#x \n", addr_inet.sin_addr.s_addr);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}