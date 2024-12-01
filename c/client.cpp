#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "socket.hpp"

//main driver program
int main(int argc, char *argv[]) {
    if (argc!=3)  {
        std::string cl = argv[0];
        std::string base_filename = cl.substr(cl.find_last_of("/\\") + 1);
        std::cout << "Usage: " << base_filename << " <input.<bin|json>> <output.<wtns|json|wshm>>\n";
    } else {
        int hSocket, read_size, server_reply;
        struct sockaddr_in server;
        t_witness_msg message;
	strcpy(message.inputFile, argv[1]);
	strcpy(message.outputFile, argv[2]);

        //Create socket
        hSocket = SocketCreate();
        if(hSocket == -1) {
            printf("Could not create socket\n");
            return 1;
        }
        //Connect to remote server
        if (SocketConnect(hSocket) < 0) {
            perror("connect failed.\n");
            return 1;
        }
        //Send data to the server, and retry until file created
        SocketSend(hSocket, (void *) &message, sizeof(t_witness_msg));

	while (1) {
          if (access(message.outputFile, F_OK) == 0) {
		  break;
	  }
	  sleep(1);
	}
    
        close(hSocket);
        shutdown(hSocket,0);
        shutdown(hSocket,1);
        shutdown(hSocket,2);
        return 0;
    }
}
