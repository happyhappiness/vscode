void h2_stream_set_suspended(h2_stream *stream, int suspended)
{
    AP_DEBUG_ASSERT(stream);
    stream->suspended = !!suspended;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
                  "h2_stream(%ld-%d): suspended=%d",
                  stream->session->id, stream->id, stream->suspended);
}