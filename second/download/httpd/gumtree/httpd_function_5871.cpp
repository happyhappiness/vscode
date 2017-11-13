apr_status_t h2_stream_write_eos(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->m->c,
                  "h2_stream(%ld-%d): closing input",
                  stream->m->id, stream->id);
    if (set_closed(stream)) {
        return h2_request_close(stream->request);
    }
    return APR_SUCCESS;
}