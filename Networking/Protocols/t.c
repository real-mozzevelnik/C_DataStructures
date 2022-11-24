#include "HTTPRequest.h"
#include <stdio.h>


int main()
{
    struct HTTPRequest req = http_request_constructor("POST /cgi-bin/process.cgi HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nHost: www.tutorialspoint.com\nContent-Type: application/x-www-form-urlencoded\nContent-Length: length\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\nConnection: Keep-Alive\n\nlicenseID=string&content=string&/paramsXML=string");
    printf("%s", (char*)req.header_fields.search(&req.header_fields, "User-Agent", sizeof("User-Agent")));

    http_request_destructor(&req);
    return 0;
}

