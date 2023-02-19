#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char **argv){

    struct sockaddr_in server_info ={0};

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1337);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info  = {0};
    socklen_t client_info_len = sizeof(client_info);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (0 > sock){
        perror("Error caused by socket");
        return -1;
    }

    if (0 > bind(sock, (struct sockaddr*)&server_info, server_info_len)){
        perror("Error caused by bind");
        return -1;
    }

    if (0 > listen(sock, 0)){
        perror("Error caused by listen");
        return -1;
    }

    int client = accept(sock, &client_info, &client_info_len);
    if (0 > client){
        perror("Error caused by accept");
        return -1;
    }

    char *hello = "Hello World!";
    ssize_t msg = send(client, (void *)hello, strlen(hello), 0);
    close(client);
}
