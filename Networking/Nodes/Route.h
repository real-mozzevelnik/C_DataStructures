#ifndef Route_h
#define Route_h

#include "HTTPServer.h"
#include "../Protocols/HTTPRequest.h"

struct Route
{
    int methods[9];
    char *uri;
    char * (*route_funcion)(struct HTTPServer *server, struct HTTPRequest *request);
};


#endif