#include "Server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor(int domain, int service, int protocol, 
    u_long interface, int port, int backlog, void (*launch)(struct Server *server))
{
    struct Server server;

    // Define basic server parameters by given.
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    
    // Construct the server's address.
    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    // Create a socket.
    server.socket = socket(domain, service, protocol);
    
    // Check the connection.
    if (server.socket == 0)
    {
        perror("Failed to connect socket...\n");
        exit(1);
    }

    // Binding the socket to the network.
    if ((bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address))) < 0)
    {
        perror("Failed to bind socket...\n");
        exit(1);
    }

    // Listening on a given port.
    if ((listen(server.socket, server.backlog)) < 0)
    {
        perror("Failed to start listening...\n");
        exit(1);
    }

    // Function given in parameters of constructor describing the server behavior.
    server.launch = launch;

    return server;
}