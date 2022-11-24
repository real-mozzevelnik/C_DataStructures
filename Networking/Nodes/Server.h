#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>

/*Struct Server is used as the foundation for nodes that need to operate as servers.
Connects to the network and listens on a given port.*/
struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface; //maybeint
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    // Function given in parameters of constructor describing the server behavior.
    void (*launch)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol, 
    u_long interface, int port, int backlog, void (*launch)(struct Server *server));

#endif