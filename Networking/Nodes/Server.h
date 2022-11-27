#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>
#include "../../DataStructures/Dictionary/Dictionary.h"

/*Struct Server is used as the foundation for nodes that need to operate as servers.
Connects to the network and listens on a given port.*/
struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    struct Dictionary routes;

    // Function given in parameters of constructor describing the server behavior.
    // void (*launch)(struct Server *server);
    void (*register_routes)(struct Server *server, char *(*route_function)(void *arg), char *path);
};

struct ServerRoute
{
    char * (*route_function)(void *arg);
};

struct Server server_constructor(int domain, int service, int protocol, 
    u_long interface, int port, int backlog);

#endif