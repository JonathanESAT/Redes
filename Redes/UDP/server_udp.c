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
    int clientes = 0;
    int bytes = 0;
    int ip_size = sizeof(ip);
    WSAStartup(MAKEWORD(2,0), &wsa);
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr = inet_addr("0.0.0.0");
    ip.sin_port = htons(9999);
    bind(sock, (SOCKADDR*)&ip, sizeof(ip));
    while(1)
    {
        memset(&pkt,0,sizeof(pkt));
        bytes = recvfrom(sock,(char*)&pkt, sizeof(pkt), 0, (SOCKADDR*)&ipc, &ip_size);
        if(pkt.tipo == 0)
        {
            clientes++;
            printf("\nNuevo cliente, clientes totales: %d", clientes);
            pkt.conn.id = clientes;
            sendto(sock,(char*)&pkt, sizeof(pkt),0,(SOCKADDR*)&ipc,sizeof(ipc));
        }
        else
        {//Paquete dato
            printf("\n El cliente %d con IP %s-->%s", pkt.data.cliente, inet_ntoa(ipc.sin_addr), pkt.data.buffer);
        }

    };
    return 0;
}