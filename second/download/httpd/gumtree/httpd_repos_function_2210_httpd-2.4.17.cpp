h2_response *h2_response_rcreate(int stream_id, request_rec *r,
                                 apr_table_t *header, apr_pool_t *pool)
{
    h2_response *response = apr_pcalloc(pool, sizeof(h2_response));
    if (response == NULL) {
        return NULL;
    }
    
    response->stream_id = stream_id;
    response->status = apr_psprintf(pool, "%d", r->status);
    response->content_length = -1;
    response->rheader = header;
    
    return response;
}