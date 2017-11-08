static h2_response *h2_response_create_int(int stream_id,
                                           int rst_error,
                                           int http_status,
                                           apr_table_t *headers,
                                           apr_table_t *notes,
                                           apr_pool_t *pool)
{
    h2_response *response;

    if (!headers) {
        return NULL;
    }
    
    response = apr_pcalloc(pool, sizeof(h2_response));
    if (response == NULL) {
        return NULL;
    }
    
    response->stream_id      = stream_id;
    response->rst_error      = rst_error;
    response->http_status    = http_status? http_status : 500;
    response->content_length = -1;
    response->headers        = headers;
    response->sos_filter     = get_sos_filter(notes);
    
    check_clen(response, NULL, pool);
    return response;
}