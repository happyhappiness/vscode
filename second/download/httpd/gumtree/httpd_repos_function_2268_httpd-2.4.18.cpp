h2_stream *h2_stream_create(int id, apr_pool_t *pool, h2_session *session)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    stream->id        = id;
    stream->state     = H2_STREAM_ST_IDLE;
    stream->pool      = pool;
    stream->session   = session;
    return stream;
}