
#ifndef __SOCKET_H__
#define __SOCKET_H__

#define FILE_LEN (1000)
#define SERVER_PORT (90190)

typedef struct {
   char inputFile[FILE_LEN];
   char outputFile[FILE_LEN];

}t_witness_msg;

short SocketCreate(void);
int SocketConnect(int hSocket);
int SocketSend(int hSocket,void* Rqst,short lenRqst);
int BindCreatedSocket(int hSocket);
int ServerInit();
int ReceiveMsg(void *message, int len);
void SocketClose(int socket);
 
#endif
