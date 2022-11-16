#include "HTTPRequest.h"
#include "../../DataStructures/Lists/Queue.h"
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
    char requested[strlen(request_string)];
    strcpy(requested, request_string);
    for (int i = 0; i <= strlen(requested) - 1; i++)
    {
        if (requested[i] == '\n' && requested[i + 1] == '\n')
        {
            printf("a/n");
            requested[i + 1] = '|';
        }
    }

    char *request_line = strtok(requested, "\n");
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

    request.header_fields = dictionary_constructor(compare_string_keys);

    struct Queue headers = queue_constructor();

    char *token = strtok(header_fields, "\n");
    while (token)
    {
        headers.push(&headers, token, sizeof(*token));
        token = strtok(NULL, "\n");
    }

    char *header = (char*)headers.peek(&headers);
    char *key;
    char *value;
    while (header)
    {
        key = strtok(header, ":");
        value = strtok(NULL, "|");
        request.header_fields.insert(&request.header_fields, key, sizeof(*key), value, sizeof(*value));
        headers.pop(&headers);
        header = (char*)headers.peek(&headers);
    }

    return request;
}