h2_response *h2_response_copy(apr_pool_t *pool, h2_response *from)
{
    h2_response *to = apr_pcalloc(pool, sizeof(h2_response));
    to->stream_id = from->stream_id;
    to->status = apr_pstrdup(pool, from->status);
    to->content_length = from->content_length;
    if (from->rheader) {
        to->ngheader = make_ngheader(pool, to->status, from->rheader);
    }
    return to;
}