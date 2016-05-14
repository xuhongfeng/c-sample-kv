#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/fcntl.h>

#include "server.h"
#include "db.h"

///// private

static const int _DEFAULT_SERVER_PORT = 8888;

static void _serverListen(Server* server) {

    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR sockfd < 0");
        exit(1);
    }
    server->socketFD = sockfd;

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server->port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(sockfd, server->tcpBacklog);
}

static void _handleClient(Server* server) {

    //TODO

    struct sockaddr_in cliAddr;
    int sockfd;
    socklen_t clilen;
    char buf[1024];
    int n;

    clilen = sizeof(cliAddr);
    while (1) {
        sockfd = accept(server->socketFD, (struct sockaddr *) &cliAddr,
                &clilen);
        if (sockfd < 0) {
            perror("ERROR on accept");
            continue;
        }

        n = read(sockfd, buf, 1024);
        if (n < 0) {
            perror("ERROR reading from socket");
            continue;
        }

        write(sockfd, buf, n);
        close(sockfd);
    }
}

///// API

Server* serverCreate() {

    Server* server = (Server*) malloc(sizeof(Server));

    // socket config
    server->port = _DEFAULT_SERVER_PORT;
    server->tcpBacklog = 1024;

    // db config
    server->db = dbCreate();

    //TODO

    return server;
}

void serverStart(Server* server) {

    _serverListen(server);
    _handleClient(server);

    //TODO
}

int main(int argc, char** argv) {
    Server* server = serverCreate();
    serverStart(server);
    return 0;
}
