#include "HTTPServer.h"
#include "Route.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

void register_routes(struct HTTPServer *server, char * (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...);

void launch(struct Server *server)
{
    int x =0;
}

struct HTTPServer http_server_constructor()
{
    struct HTTPServer server;
    server.server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 255, launch);
    server.routes = dictionary_constructor(compare_string_keys);
    server.register_routes = register_routes;
    return server;
}

void register_routes(struct HTTPServer *server, char * (*route_function)(struct HTTPServer *server, struct HTTPRequest *request), char *uri, int num_methods, ...)
{
    struct Route route;
    va_list methods;
    va_start(methods, num_methods);
    for (int i = 0; i < num_methods; i++)
    {
        route.methods[i] = va_arg(methods, int);
    }
    route.uri = (char*)malloc(sizeof(char)*strlen(uri)+1); // modified
    strcpy(route.uri, uri);
    route.route_funcion = route_function;

    server->routes.insert(&server->routes, uri, sizeof(char)*strlen(uri)+1, &route, sizeof(route));
}
