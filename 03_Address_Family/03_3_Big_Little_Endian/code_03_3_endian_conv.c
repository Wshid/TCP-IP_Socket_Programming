#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char** argv)
{
    unsigned short host_port=0x1234;
    unsigned short net_port;
    unsigned long host_addr=0x12345678;
    unsigned long net_addr;
    
    net_port=htons(host_port);
    net_addr=htonl(host_addr);
    
    printf("Host port : %#x \n", host_port); // %x => unsigned int
    printf("Network port : %#x\n", net_port);
    printf("Host address : %#lx\n", host_addr); // %lx => long unsigned int
    printf("Network address : %#lx\n", net_addr);
    return 0; // #이 있으면 0x형태로 나타내줌
}