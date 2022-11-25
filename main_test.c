#include <stdio.h>
#include <stdlib.h>
#include "Networking/Nodes/HTTPServer.h"

char * f(struct HTTPServer *server, struct HTTPRequest *request)
{
    return 0;
}

int main()
{
    struct HTTPServer http = http_server_constructor();
    http.register_routes(&http, f, "hkjlj", 1, 1);

    return 0;
}
