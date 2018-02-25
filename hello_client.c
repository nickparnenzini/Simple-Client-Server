#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEN_REPLY 6

int main(int argc, char* argv[]) {

    char *srv_ip = argv[0];
    char *process_number;
    int ret, sd;   
    long port;
    struct sockaddr_in sv_addr; 
    char buffer[1024];
    int len = LEN_REPLY;

    port = strtol(argv[1],&process_number,10);

    /* New socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);

    /* Address of the server */
    memset(&sv_addr, 0, sizeof(sv_addr)); // Pulizia
    sv_addr.sin_family = AF_INET ;
    sv_addr.sin_port = htons(port);
    inet_pton(AF_INET, srv_ip, &sv_addr.sin_addr);

    ret = connect(sd, (struct sockaddr*)&sv_addr, sizeof(sv_addr));
    if (ret < 0) {
    	perror("Error while connecting to the server... \n");
    	exit(-1);
    }

    ret = recv(sd, (void*)buffer, len, 0);
    
    if(ret < 0){
        perror("Error while receiving a message from the server: \n");
        exit(-1);
    }

    buffer[len] = '\0';
    printf("%s\n", buffer);

    close(sd);

	  return 0;
}
