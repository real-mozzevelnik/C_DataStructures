#include "HTTPRequest.h"
#include <string.h>
#include <stdlib.h>

int method_select(char *method)
{
    if (! strcmp(method, "GET"))
    {
        return GET;
    }
    else if (! strcmp(method, "POST"))
    {
        return POST;
    }
    else if (! strcmp(method, "PUT"))
    {
        return PUT;
    }
    else if (! strcmp(method, "HEAD"))
    {
        return HEAD;
    }
    else if (! strcmp(method, "PATCH"))
    {
        return PATCH;
    }
    else if (! strcmp(method, "DELETE"))
    {
        return DELETE;
    }
    else if (! strcmp(method, "CONNECT"))
    {
        return CONNECT;
    }
    else if (! strcmp(method, "OPTIONS"))
    {
        return OPTIONS;
    }
    else if (! strcmp(method, "TRACE"))
    {
        return TRACE;
    }
}

struct HTTPRequest http_request_constructor(char *request_string)
{
    struct HTTPRequest request;

    for (int i = 0; i <= strlen(request_string) - 1; i++)
    {
        if (request_string[i] == '\n' && request_string[i + 1] == '\n')
        {
             request_string[i + 1] = '|';
        }
    }

    char *request_line = strtok(request_string, "\n");
    char *header_fields = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    
    
    char *method = strtok(request_line, " ");
    request.Method = method_select(method);
    char *URI = strtok(NULL, " ");
    request.URI = URI;
    char *HTTPVersion = strtok(NULL, " ");
    HTTPVersion = strtok(HTTPVersion, "/");
    HTTPVersion = strtok(NULL, "/");
    request.HTTPVersion = (float)atof(HTTPVersion);
    
    
    return request;
}