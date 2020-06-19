#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define PORTNUM 3389
 struct SendPacket{
    char ip[1000];
    char host[1000];
    char port[256];
};
int main(void){
    int sd;
    struct sockaddr_in sin;
    struct SendPacket sPacket;
    int GetSize;
    char suBuffer[1000];
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("10.178.0.2");
    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }
    GetSize = recv(sd,(struct SendPacket*)&sPacket,sizeof(sPacket),0);
    printf("%s \n", sPacket.host);
    printf("%s \n",sPacket.ip);
    printf("%s \n",sPacket.port);
    close(sd);
    return 0;
}
