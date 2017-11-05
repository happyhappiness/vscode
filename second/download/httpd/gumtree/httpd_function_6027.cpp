void h2_stream_cleanup(h2_stream *stream)
{
    AP_DEBUG_ASSERT(stream);
    if (stream->buffer) {
        apr_brigade_cleanup(stream->buffer);
    }
    if (stream->input) {
        apr_status_t status;
        status = h2_beam_shutdown(stream->input, APR_NONBLOCK_READ, 1);
        if (status == APR_EAGAIN) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                          "h2_stream(%ld-%d): wait on input shutdown", 
                          stream->session->id, stream->id);
            status = h2_beam_shutdown(stream->input, APR_BLOCK_READ, 1);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                          "h2_stream(%ld-%d): input shutdown returned", 
                          stream->session->id, stream->id);
        }
    }
}