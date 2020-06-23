# C_Socket_

-----

위 프로그램은 서버에 접속한 클라이언트의 호스트명, Ip, 포트 정보를 확인 후 클라이언트에게 보내는 server, client 프로그램.

#### Test Environment

``` GCP Instance Ubuntu 18.0.4 LTS ```

#### main Implementation And Difficult 

문제점 발견: TCP Stream으로 send를 한 번여 여러개 받아들이지 못하였다.

처음 접근: send 3번 recv 3번 -> 그래도 동일하게 처음 send만 전송됨.

```해결책 접근: 구조체를 이용해서 구조체 전체를 통신하자```

##### How?

+ 소켓 통신을 이용해 구조체 전송

  1. 구조체 선언

     ```c
     struct SendPacket{
         char ip[1000];
         char host[1000];
         char port[256];
     };
     ```

2.  구조체 전송 (server.c)

   ```c
   if (send(ns,(struct SendPacket*)&sPacket,sizeof(sPacket),0)  == -1) {
             perror("send");
             exit(1);
         }
   ```

3. 구조체 받기 (client.c)

```c
GetSize = recv(sd,(struct SendPacket*)&sPacket,sizeof(sPacket),0);
```

