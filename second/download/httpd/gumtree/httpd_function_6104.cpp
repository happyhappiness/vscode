h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    stream->id        = id;
    stream->state     = H2_STREAM_ST_IDLE;
    stream->pool      = pool;
    stream->session   = session;
    set_state(stream, H2_STREAM_ST_OPEN);
    stream->request   = h2_request_create(id, pool, 
        h2_config_geti(session->config, H2_CONF_SER_HEADERS));
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}