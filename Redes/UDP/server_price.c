#include "stdio.h"
#include "WinSock2.h"
#include "estructuras.h"
#pragma comment(lib,"ws2_32.lib")


struct players{
    int id_player;
    char nombre[100];
    struct sockaddr_in ip;
};

int main()
{
    WSADATA wsa;
    SOCKET sock;
    struct PKT pkt;
    int clientes = 0;
    struct players players[4];
    struct sockaddr_in ip, iptmp;
    int ip_size = sizeof(ip);
    WSAStartup(MAKEWORD(2,0), &wsa);
    sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    ip.sin_family = AF_INET;
    ip.sin_addr.s_addr=inet_addr("0.0.0.0");
    ip.sin_port=htons(99990);
    bind(sock, (SOCKADDR*)&ip, sizeof(ip));
    while(1)
    {

        memset(&pkt,0,sizeof(pkt));
        recvfrom(sock,(char*)&pkt,sizeof(pkt), 0, (SOCKADDR*)&iptmp, &ip_size);
        if(pkt.tipo==ePKT_CONN)
        {
            printf("\n Nuevo cliente:%s",pkt.conn.nombre);
            strcpy(players[clientes].nombre, pkt.conn.nombre);
            players[clientes].id_player = clientes;
            players[clientes].ip = iptmp;
            sendto(sock,(char*)&pkt,sizeof(pkt),0,(SOCKADDR*)&iptmp,sizeof(iptmp));
            clientes++;
        }
    } 
    return 0;
}
