#include "stdio.h"
#include "WinSock2.h"
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    struct sockaddr_in ip, ipc;
    SOCKET sock;
    int broad = 1;
    char buffer[512] = {0};
    WSAStartup(MAKEWORD(2,0), &wsa);
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = inet_addr("255.255.255.255");
    ip.sin_port = htons(8888);
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST,(char*)&broad,sizeof(broad));
    sendto(sock,"Hola",4,0,(SOCKADDR*)&ip,sizeof(ip));
    recvfrom(sock,buffer,sizeof(buffer), 0,NULL,NULL);
    printf("\nRecibido: %s", buffer);
    return 0;

}