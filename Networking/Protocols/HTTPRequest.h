#ifndef HTTPRequest_h
#define HTTPRequest_h

#include "../../DataStructures/Dictionary/Dictionary.h"

/*Struct HTTPServer contains three dictionaries of three components of HTTP request:
request line, headers and body.
Uses memory allocation.*/
struct HTTPRequest
{
    struct Dictionary request_line;
    struct Dictionary header_fields;
    struct Dictionary body;
};

struct HTTPRequest http_request_constructor(char *request_string); //const may be
// Free allocated memory.
void http_request_destructor(struct HTTPRequest *request);

#endif