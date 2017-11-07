void h2_stream_cleanup(h2_stream *stream)
{
    apr_status_t status;
    
    ap_assert(stream);
    if (stream->out_buffer) {
        /* remove any left over output buckets that may still have
         * references into request pools */
        apr_brigade_cleanup(stream->out_buffer);
    }
    h2_beam_abort(stream->input);
    status = h2_beam_wait_empty(stream->input, APR_NONBLOCK_READ);
    if (status == APR_EAGAIN) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
                      "h2_stream(%ld-%d): wait on input drain", 
                      stream->session->id, stream->id);
        status = h2_beam_wait_empty(stream->input, APR_BLOCK_READ);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
                      "h2_stream(%ld-%d): input drain returned", 
                      stream->session->id, stream->id);
    }
}