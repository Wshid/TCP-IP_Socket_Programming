/*
#include<stdio.h>

in_addr_t inet_addr(const char *string) // 문자열 IP -> 32비트 정수형 변환

*/

#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char** argv)
{
    char *addr1="1.2.3.4";
    char *addr2="1.2.3.256";
    
    unsigned long conv_addr=inet_addr(addr1); // 네트워크 바이트 순서로 반환
    if(conv_addr==INADDR_NONE) printf("Error occured! \n");
    else printf("Network ordered integer addr : %#lx \n", conv_addr);
    
    conv_addr=inet_addr(addr2);
    
    if(conv_addr==INADDR_NONE) printf("Error occured! \n");
    else printf("Network ordered integer addr : %#lx \n", conv_addr); // .256은 주소에 맞지 않음
    return 0;
    
}