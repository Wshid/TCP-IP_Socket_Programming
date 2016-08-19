/* WSAStringtoAddress & WSAAddressToString 
    inet_ntoa, inet_addr과 기능은 같으나 다양한 프로토콜에 적용 가능
        윈도우에 종속적인 프로그래밍이 됨
            => inet_계열 함수보다 이식성이 떨어짐
    
    #include<winsock2.h>
    
    INT WSAStringToAddress(
        LPTSTR                  AddressString, // IP,PORT담은 문자열 주소값
        INT                     AddressFamily, // 주소정보가 속하는 주소체계 전달
        LPWSAPROTOCOL_INFO      lpProtocolInfo // Protocol Provider, 보통은 NULL
        LPSOCKADDR lpAddress    lpAddress // 주소정보를 담을 구조체 변수의 주소값 전달
        LPINT                   lpAddressLength // 주소값의 변수크기를 담은 변수의 주소값
    ); // 성공시 0, 실패시 SOCKET_ERROR
    
    INT WSAAddressToString(
        LPSOCKADDR                      lpsaAddress, // 문자열로 변환할 주소정보 구조체 변수 주소값
        DWORD                           dwAddressLength, // 첫번째 인자 구조체 크기
        LPWSAPROTOCOL_INFO              lpProtocolInfo, // Protocol Provider, 보통 NULL
        LPTSTR                          lpszAddressString // 문자열로 변환된 결과를 저장할 배열 주소값
        LPDWORD                         lpdwAddressStringLength // 네번째 인자 크기, 주소값 전달
    );
*/

#undef UNICODE
#undef _UNICODE
#include<stdio.h>
#include<winsock2.h>

int main(int argc, char** argv)
{
    char *strAddr="203.211.218.102:9190";
    
    char strAddrBuf[50];
    SOCKADDR_IN serv_addr;
    int size;
    
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    
    size=sizeof(strAddr);
    WSAStringToAddress(strAddr, AF_INET, NULL, (SOCKADDR*)&serv_addr, &size);
    
    size=sizeof(strAddrBuf);
    WSAAddressToString((SOCKADDR*)&serv_addr, sizeof(serv_addr), NULL, strAddrBuf, &size);
    
    printf("Second conv result : %s \n", strAddrBuf);
    WSACleanup();
    return 0;
}