#ifndef HTTPServer_h
#define HTTPServer_h

#include "Server.h"
#include "../Protocols/HTTPRequest.h"
#include "../../DataStructures/Dictionary/Dictionary.h"

struct HTTPServer
{
    struct Server server;

    struct Dictionary routes;

    void (*register_routes)(struct HTTPServer *server, char * (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...);
    void (*launch)(struct HTTPServer *server);
};

enum HTTPMethods
{
    CONNECT,
    DELETE,
    GET,
    HEAD,
    OPTIONS,
    PATCH,
    POST,
    PUT,
    TRACE
};

struct HTTPServer http_server_constructor(void);

char *render_template(int num_templates, ...);

#endif