#include "HTTPRequest.h"
#include "../../DataStructures/Lists/Queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Functions for extracting elements of relevant request parts.
void extract_request_line_fields(struct HTTPRequest *request, char *request_line);
void extract_header_fields(struct HTTPRequest *request, char *header_fields);
void extract_body(struct HTTPRequest *reauest, char *body);

// Parses the given request string into three dictionaries.
struct HTTPRequest http_request_constructor(char *request_string)
{
    // New object.
    struct HTTPRequest request;

    // Allocate some memory and copy given string so we able to change it.
    char *requested = (char*)malloc(strlen(request_string)+1);
    strcpy(requested, request_string);

    // Replace the blank line with '|'. So we can separate request parts.
    int cycle_var = strlen(requested) - 2;
    for (int i = 0; i <= cycle_var; i++)
    {
        if (requested[i] == '\n' && requested[i + 1] == '\n')
        {
            // Make it possible to separate headers from the body.
            requested[i + 1] = '|';
        }
    }

    // Separate the request string into three parts.
    char *request_line = strtok(requested, "\n");
    char *header_fields = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    // Parse each section into the dictionary.
    extract_request_line_fields(&request, request_line);
    extract_header_fields(&request, header_fields);
    extract_body(&request, body);

    // Free the copy of given string.
    free(requested);
    return request;
}

// Destroys all dictionaries, so allocated memory is free.
void http_request_destructor(struct HTTPRequest *request)
{
    dictionary_destructor(&request->request_line);
    dictionary_destructor(&request->header_fields);
    dictionary_destructor(&request->body);
}

// Parses the request line to retrieve the method, uri and hhtp version.
void extract_request_line_fields(struct HTTPRequest *request, char *request_line)
{
    // Allocate memory and copy the given string.
    char *fields = (char*)malloc(strlen(request_line)+1);
    strcpy(fields, request_line);

    // Separate each section of request line.
    char *method = strtok(fields, " ");
    char *uri = strtok(NULL, " ");
    char *http_version = strtok(NULL, "\0"); // gives for example "HTTP/1.1"
    http_version = strtok(http_version, "/"); // gives HTTP
    http_version = strtok(NULL, "/"); //gives 1.1
    float http_ver = (float)atof(http_version); // converts string to float.

    // Insert the results into dictionary.
    struct Dictionary request_line_dict = dictionary_constructor(compare_string_keys);
    request_line_dict.insert(&request_line_dict, "method", sizeof("method"), method, sizeof(char)*strlen(method)+1);
    request_line_dict.insert(&request_line_dict, "uri", sizeof("uri"), uri, sizeof(char)*strlen(uri)+1);
    request_line_dict.insert(&request_line_dict, "http_version", sizeof("http_version"), &http_ver, sizeof(http_ver));

    // Save the dictionary to the request struct.
    request->request_line = request_line_dict;
    
    // If this is GET request, it doesn't have body part.
    // So uri passed in the body dictionary.
    if (request->request_line.search(&request->request_line, "GET", sizeof("GET")))
    {
        extract_body(request, (char *)request->request_line.search(&request->request_line, "uri", sizeof("uri")));
    }
    // Free the copy of given string.
    free(fields);
}

// Parses header fields.
void extract_header_fields(struct HTTPRequest *request, char *header_fields)
{
    // Allocate memory and copy the given string.
    char *fields = (char*)malloc(strlen(header_fields)+1);
    strcpy(fields, header_fields);

    // Save each line into queue.
    struct Queue headers = queue_constructor();
    char *field = strtok(fields, "\n");
    while (field)
    {
        // Separates strokes and inserts it into queue.
        headers.push(&headers, field, sizeof(char)*strlen(field)+1);
        field = strtok(NULL, "\n");
    }

    // Initialize the header fields dicrionary.
    request->header_fields = dictionary_constructor(compare_string_keys);

    // Parse each stroke in queue into key-value pair and insert it in dictionary.
    char *header = (char *)headers.peek(&headers);
    while (header)
    {
        char *key = strtok(header, ":");
        char *value = strtok(NULL, "\0");

        if (value)
        {
            // Remove the whitespaces.
            if (value[0] == ' ')
                value++;
            
            request->header_fields.insert(&request->header_fields, key, sizeof(char)*strlen(key)+1, value, sizeof(char)*strlen(value)+1);
        }
        // Delete stroke from queue and get the new one.
        headers.pop(&headers);
        header = (char *)headers.peek(&headers);
    }
    // Desroy the queue.
    queue_destructor(&headers);
    // Free the copy of given string.
    free(fields);
}

// Parses the body according to the content type.
void extract_body(struct HTTPRequest *request, char *body)
{
    // Allocate memory and copy the given string.
    char *body_to_extract = (char*)malloc(strlen(body)+1);
    strcpy(body_to_extract, body);

    // Check if there is content type in headers.
    // If this is GET request, it doesn't contain content type, so it won't be parsed twice.
    char *content_type = (char *)request->header_fields.search(&request->header_fields, "Content-Type", sizeof("Content-Type"));
    if (content_type)
    {
        // Initialize the dictionary.
        struct Dictionary body_fields = dictionary_constructor(compare_string_keys);

        if (strcmp(content_type, "application/x-www-form-urlencoded") == 0)
        {
            // Collect each key-value pair into queue by parsing it
            struct Queue fields = queue_constructor();
            char *field = strtok(body_to_extract, "&");
            while (field)
            {
                fields.push(&fields, field, sizeof(char)*strlen(field)+1);
                field = strtok(NULL, "&");
            }
            // Iterate over queue to separate keys from values and insert them to the dictionary.
            field = fields.peek(&fields);
            while (field)
            {
                char *key = strtok(field, "=");
                char *value = strtok(NULL, "\0");
                // Remove the whitespace.
                if (value[0] == ' ')
                    value++;
                
                body_fields.insert(&body_fields, key, sizeof(char)*strlen(key)+1, value, sizeof(char)*strlen(value)+1);

                // Remove item from queue and get a new one.
                fields.pop(&fields);
                field = fields.peek(&fields);
            }
            // Destroy the queue.
            queue_destructor(&fields);
        }
        // Save the body as unseparated stroke.
        else
        {
            body_fields.insert(&body_fields, "data", sizeof("data"), body_to_extract, sizeof(char)*strlen(body)+1);
        }
        // Set the request's dictionary.
        request->body = body_fields;
    }
    // Free the copy of given string.
    free(body_to_extract);
}