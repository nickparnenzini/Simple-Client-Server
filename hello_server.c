#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {

    char *host = argv[0];
    char *process_number;
    long port;
    int ret, server_sd, len, client_sd;
    struct sockaddr_in server_address, client_address; 

    int newfd;
    int addrlen;
    char buffer[1024];

    port = strtol(argv[1],&process_number,10);

    /* new socket */
    server_sd = socket(AF_INET,SOCK_STREAM,0);

    /* Creating address */
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, host, &server_address.sin_addr);

    /* Assign the specific address to the socket */
    ret = bind(server_sd,(struct sockaddr*)&server_address, sizeof(server_address));
    if (ret < 0) {
        perror("Error during bind: \n");
        exit(-1);
    }

    ret = listen(server_sd,10);
    if (ret < 0) {
      perror("Error during listen: \n");
      exit(-1);
    }

    while(1) {
        newfd = accept(server_sd,(struct sockaddr *)&client_address, &addrlen);

        strcpy(buffer, "Hello!");
        printf("Hello!\n");
        addrlen = strlen(buffer);
        ret = send(newfd, (void*) buffer, len, 0);

        if(ret < 0){
          perror("Error while sending a message to the client: \n");
          close(newfd);
        }	    		
    }

    return 0;
}
