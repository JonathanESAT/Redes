#include <stdio.h>
#include "winsock.h"
#include "string.h"
#include "estructuras.h"
#pragma comment(lib, "ws2_32.lib")

int main(){
    WSADATA wsa;
    struct sockaddr_in ip, ipc;
    SOCKET sock;
    struct packet pkt;
    int id_cliente = 0;
    int ip_size = sizeof(ip);
    WSAStartup(MAKEWORD(2,0), &wsa);
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = inet_addr("127.0.0.1");
    ip.sin_port = htons(9999);
    while(id_cliente==0)
    {
        memset(&pkt,0,sizeof(pkt));
        sendto(sock,(char*)&pkt,sizeof(pkt),0,(SOCKADDR*)&ip,sizeof(ip));
        recvfrom(sock,(char*)&pkt,sizeof(pkt),0,NULL,NULL);
        id_cliente = pkt.conn.id;

    }

    printf("\nID:%d", id_cliente);
    while(1){
        printf("\n Introduzca Cadena: ");
        fgets(pkt.data.buffer,sizeof(pkt.data.buffer),stdin);
        pkt.data.cliente = id_cliente;
        pkt.tipo = 1;
        sendto(sock,(char*)&pkt,sizeof(pkt),0,(SOCKADDR*)&ip,sizeof(ip));
    }


return 0;
}