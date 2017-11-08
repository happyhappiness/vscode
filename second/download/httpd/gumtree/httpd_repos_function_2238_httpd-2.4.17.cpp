void h2_stream_attach_pool(h2_stream *stream, apr_pool_t *pool)
{
    stream->pool = pool;
}