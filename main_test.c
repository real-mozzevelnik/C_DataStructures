#include <stdio.h>
#include <stdlib.h>
#include "Networking/Nodes/HTTPServer.h"
#include "System/ThreadPool.h"

char * home(struct HTTPServer *server, struct HTTPRequest *request)
{
    char *x = render_template(1, "/home/vadimchumachenko/progs/c/p2p/index.html");
    return x;
}

char * about(struct HTTPServer *server, struct HTTPRequest *request)
{
    return render_template(1, "/home/vadimchumachenko/progs/c/p2p/about.html");
}

int main()
{
    // struct HTTPServer server;
    struct HTTPServer server = http_server_constructor();

    server.register_routes(&server, home, "/", 0);
    server.register_routes(&server, about, "/about", 0);

    server.launch(&server);


    return 0;
}
