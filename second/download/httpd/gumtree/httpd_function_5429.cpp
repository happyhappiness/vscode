static apr_status_t make_h2_headers(h2_from_h1 *from_h1, request_rec *r)
{
    from_h1->response = h2_response_create(from_h1->stream_id, 0,
                                           from_h1->http_status, from_h1->hlines,
                                           from_h1->pool);
    from_h1->content_length = from_h1->response->content_length;
    from_h1->chunked = r->chunked;
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection,
                  "h2_from_h1(%d): converted headers, content-length: %d"
                  ", chunked=%d",
                  from_h1->stream_id, (int)from_h1->content_length, 
                  (int)from_h1->chunked);
    
    set_state(from_h1, ((from_h1->chunked || from_h1->content_length > 0)?
                        H2_RESP_ST_BODY : H2_RESP_ST_DONE));
    /* We are ready to be sent to the client */
    return APR_SUCCESS;
}