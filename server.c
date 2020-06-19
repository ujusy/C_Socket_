#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define PORTNUM 3389
int main(void) {
struct SendPacket{
    char ip[1000];
    char host[1000];
    char port[256];
};
    struct sockaddr_in sin, cli;
    struct hostent *host_entry;
    int sd, ns, ndx, clientlen = sizeof(cli);
    int sa;
    struct SendPacket sPacket;
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    exit(1);
    }
    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORTNUM);
    sin.sin_addr.s_addr = inet_addr("10.178.0.2");
    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("bind");
            exit(1);
      }
    if (listen(sd, 5)) {
          perror("listen");
          exit(1);
      }
      if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen))==-1){
          perror("accept");
         exit(1);
      }
    host_entry = gethostbyaddr((char*)&cli.sin_addr, 4, AF_INET);
     sprintf(sPacket.host, "Get From Server - My Host Name %s", host_entry->h_name);
    sprintf(sPacket.ip, "Get From Server - My IP Addresss %s", inet_ntoa(cli.sin_addr));
    sprintf(sPacket.port,"Get From Server - My Port Number %d", ntohs(cli.sin_port));
    if (send(ns,(struct SendPacket*)&sPacket,sizeof(sPacket),0)  == -1) {
          perror("send");
          exit(1);
      }
      close(ns);
      printf("Client Info - Host Name: %s\n", host_entry->h_name);
      printf("Client Info - IP Address: %s\n",inet_ntoa(cli.sin_addr));
      printf("Client Info - Port Number %d\n", ntohs(cli.sin_port));
      close(sd);
      return 0;
  }
