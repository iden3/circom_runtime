#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "socket.hpp"

static int SocketDesc;

//Create a Socket for server communication
short SocketCreate(void) {
    short hSocket;
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}

int SocketConnect(int hSocket) {
    int iRetval=-1;
    int ServerPort = SERVER_PORT;
    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);
    iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
    return iRetval;
}

// Send the data to the server and set the timeout of 20 seconds
int SocketSend(int hSocket,void* Rqst,short lenRqst) {
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = send(hSocket, Rqst, lenRqst, 0);
    return shortRetval;
}

int BindCreatedSocket(int hSocket) {
    int iRetval=-1;
    int ClientPort = SERVER_PORT;
    struct sockaddr_in  remote= {0};
    /* Internet address family */
    remote.sin_family = AF_INET;
    /* Any incoming interface */
    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(ClientPort); /* Local port */
    iRetval = bind(hSocket,(struct sockaddr *)&remote,sizeof(remote));
    return iRetval;
}


int ServerInit() {
   //Create socket
   SocketDesc = SocketCreate();
   if (SocketDesc == -1) {
       printf("Could not create socket");
       return 0;
    }
   //Bind
   if( BindCreatedSocket(SocketDesc) < 0) {
      //print the error message
       perror("bind failed.");
       return 0;
   }
   //Listen
   listen(SocketDesc, 3);

   return 1;
}

int ReceiveMsg(void *message, int len) {
   int sock, clientLen;
   struct sockaddr_in client;
   printf("Waiting for incoming connections...\n");
   clientLen = sizeof(struct sockaddr_in);
   //accept connection from an incoming client
   sock = accept(SocketDesc,(struct sockaddr *)&client,(socklen_t*)&clientLen);
   if (sock < 0) {
       perror("accept failed");
       return 0;
   }
   printf("Connection accepted\n");
   //Receive a reply from the client
   if( recv(sock, message, sizeof(t_witness_msg), 0) < 0) {
      printf("recv failed");
      return 0;
   }
   return sock;
}

void SocketClose(int socket) {
   close(socket);
}
