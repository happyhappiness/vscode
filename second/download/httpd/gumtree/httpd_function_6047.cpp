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
    
    return response;
}