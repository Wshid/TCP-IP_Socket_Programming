/*
#include<arpa/inet.h>

char* inet_ntoa(struct in_addr adr); //정수형태의 IP -> 문자열형태의 IP정보
    return 값이 char*포인터, 문자열이 메모리공간에 저장되었다는 것이므로,
    다른 곳에 저장해두지 않으면 값 변환이 일어날 수 있음
*/

#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc, char** argv)
{
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];
    
    addr1.sin_addr.s_addr=htonl(0x1020304);
    addr2.sin_addr.s_addr=htonl(0x1010101);
    
    str_ptr=inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("Dotted-Decimal notation1 : %s\n", str_ptr);
    
    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation1 : %s\n", str_ptr);
    printf("Dotted-Decimal notation1 : %s\n", str_arr);
    return 0;
}