#include "HTTPRequest.h"
#include <stdio.h>


int main()
{
    struct HTTPRequest req = http_request_constructor("POST /cgi-bin/process.cgi HTTP/1.1\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\nHost: www.tutorialspoint.com\nContent-Type: application/x-www-form-urlencoded\nContent-Length: length\nAccept-Language: en-us\nAccept-Encoding: gzip, deflate\nConnection: Keep-Alive\n\nlicenseID=string&content=string&/paramsXML=string");
    float *h = (float*)req.request_line.search(&(req.request_line), "http_version", sizeof("http_version"));
    // printf("%lf", *h);
    return 0;
}

