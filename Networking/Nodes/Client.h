#ifndef Client_h
#define Client_h

#include <sys/socket.h>
#include <netinet/in.h>

struct Client
{
    int domain;
    int service;
    int protocol;
    int port;
    u_long interface;

    int socket;

    char * (*request)(struct Client *client, char *server_ip, char *request, int size);
};

struct Client client_constructor(int domain, int service, int protocol, int port, u_long interface);

#endif