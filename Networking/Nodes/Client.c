#include "Client.h"
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char * request(struct Client *client, char *server_ip, char *request, int size);

struct Client client_consturctor(int domain, int service, int protocol, int port, u_long interface)
{
    struct Client client;
    client.domain = domain;
    client.port = port;
    client.interface = interface;
    client.service = service;
    client.protocol = protocol;

    client.socket = socket(domain, service, protocol);
    
    client.request = request;

    return client;
}

char * request(struct Client *client, char *server_ip, char *request, int size)
{
    struct sockaddr_in server_address;
    server_address.sin_family = client->domain;
    server_address.sin_port = htons(client->port);
    server_address.sin_addr.s_addr = (int)client->interface;

    inet_pton(client->domain, server_ip, &server_address.sin_addr);

    connect(client->socket, (struct sockaddr*)&server_address, sizeof(server_address));

    send(client->socket, request, size, 0);

    char response[30000];
    read(client->socket, response, 30000);

    return response;
}