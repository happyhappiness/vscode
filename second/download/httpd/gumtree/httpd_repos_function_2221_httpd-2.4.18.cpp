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