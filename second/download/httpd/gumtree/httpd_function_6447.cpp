apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
                                h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    AP_DEBUG_ASSERT(stream);
    AP_DEBUG_ASSERT(stream->session);
    AP_DEBUG_ASSERT(stream->session->mplx);
    
    if (!output_open(stream)) {
        return APR_ECONNRESET;
    }
    if (stream->scheduled) {
        return APR_EINVAL;
    }
    if (eos) {
        close_input(stream);
    }
    
    /* Seeing the end-of-headers, we have everything we need to 
     * start processing it.
     */
    status = h2_request_end_headers(stream->request, stream->pool, 
                                    eos, push_enabled);
    if (status == APR_SUCCESS) {
        if (!eos) {
            stream->request->body = 1;
        }
        stream->input_remaining = stream->request->content_length;
        
        status = h2_mplx_process(stream->session->mplx, stream->id, 
                                 stream->request, cmp, ctx);
        stream->scheduled = 1;
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    else {
        h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                      stream->session->id, stream->id,
                      stream->request->method, stream->request->scheme,
                      stream->request->authority, stream->request->path);
    }
    
    return status;
}