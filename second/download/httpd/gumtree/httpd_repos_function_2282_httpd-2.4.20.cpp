apr_status_t h2_stream_destroy(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
    return APR_SUCCESS;
}