#include "HTTPRequest.h"
#include <stdio.h>


int main()
{
    struct HTTPRequest req = http_request_constructor("GET /cgi-bin/process.cgi HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nHost: www.tutorialspoint.com\nContent-Type: application/x-www-form-urlencoded\nContent-Length: length\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\nConnection: Keep-Alive\n\nlicenseID=string&content=string&/paramsXML=string");
    printf("\n\n%s\n", (char*)req.body.search(&req.body, "data", sizeof("data")));

    http_request_destructor(&req);
    return 0;
}

