void h2_stream_destroy(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                  "h2_stream(%ld-%d): destroy", 
                  stream->session->id, stream->id);
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
}