    }
    else {
        return apr_table_make(pool, 0);        
    }
}

static h2_response *h2_response_create_int(int stream_id,
                                           int rst_error,
                                           int http_status,
                                           apr_table_t *headers,
                                           apr_pool_t *pool)
{
    h2_response *response;
    const char *s;

    if (!headers) {
        return NULL;
    }
    
    response = apr_pcalloc(pool, sizeof(h2_response));
    if (response == NULL) {
        return NULL;
    }
    
    response->stream_id = stream_id;
    response->rst_error = rst_error;
    response->http_status = http_status? http_status : 500;
    response->content_length = -1;
    response->headers = headers;
    
    s = apr_table_get(headers, "Content-Length");
    if (s) {
        char *end;
        
        response->content_length = apr_strtoi64(s, &end, 10);
        if (s == end) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, APR_EINVAL, 
                          pool, APLOGNO(02956) 
                          "h2_response: content-length"
                          " value not parsed: %s", s);
            response->content_length = -1;
        }
    }
    return response;
}


h2_response *h2_response_create(int stream_id,
                                int rst_error,
                                int http_status,
                                apr_array_header_t *hlines,
                                apr_pool_t *pool)
{
    return h2_response_create_int(stream_id, rst_error, http_status,
                                  parse_headers(hlines, pool), pool);
}

h2_response *h2_response_rcreate(int stream_id, request_rec *r,
                                 apr_table_t *header, apr_pool_t *pool)
{
    h2_response *response = apr_pcalloc(pool, sizeof(h2_response));
    if (response == NULL) {
        return NULL;
    }
    
    response->stream_id = stream_id;
    response->http_status = r->status;
    response->content_length = -1;
    response->headers = header;

    if (response->http_status == HTTP_FORBIDDEN) {
        const char *cause = apr_table_get(r->notes, "ssl-renegotiate-forbidden");
        if (cause) {
            /* This request triggered a TLS renegotiation that is now allowed 
             * in HTTP/2. Tell the client that it should use HTTP/1.1 for this.
             */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, response->http_status, r, 
                          "h2_response(%ld-%d): renegotiate forbidden, cause: %s",
                          (long)r->connection->id, stream_id, cause);
            response->rst_error = H2_ERR_HTTP_1_1_REQUIRED;
        }
    }
    
