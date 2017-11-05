h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session)
{
    h2_stream *stream = h2_stream_create(id, pool, session);
    set_state(stream, H2_STREAM_ST_OPEN);
    stream->request   = h2_request_create(id, pool, session->config);
    stream->bbout     = apr_brigade_create(stream->pool, 
                                           stream->session->c->bucket_alloc);
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}