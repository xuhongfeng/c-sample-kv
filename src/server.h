#ifndef __SERVER_H
#define __SERVER_H

#include "db.h"

typedef struct Server {
    int port;
    int tcpBacklog;
    int socketFD;
    Db* db;
} Server;

Server* serverCreate();
void serverStart(Server* server);

#endif
