{
    return from_h1->response;
}

static apr_status_t make_h2_headers(h2_from_h1 *from_h1, request_rec *r)
{
    from_h1->response = h2_response_create(from_h1->stream_id, 
                                       from_h1->status, from_h1->hlines,
                                       from_h1->pool);
    if (from_h1->response == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EINVAL, r->connection,
                      APLOGNO(02915) 
                      "h2_from_h1(%d): unable to create resp_head",
                      from_h1->stream_id);
        return APR_EINVAL;
    }
    from_h1->content_length = from_h1->response->content_length;
    from_h1->chunked = r->chunked;
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection,
                  "h2_from_h1(%d): converted headers, content-length: %d"
                  ", chunked=%d",
