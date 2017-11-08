h2_response *h2_response_clone(apr_pool_t *pool, h2_response *from)
{
    h2_response *to = apr_pcalloc(pool, sizeof(h2_response));
    to->stream_id = from->stream_id;
    to->http_status = from->http_status;
    to->content_length = from->content_length;
    if (from->headers) {
        to->headers = apr_table_clone(pool, from->headers);
    }
    if (from->trailers) {
        to->trailers = apr_table_clone(pool, from->trailers);
    }
    return to;
}