static apr_status_t on_stream_resume(void *ctx, h2_stream *stream)
{
    h2_session *session = ctx;
    apr_status_t status = APR_EAGAIN;
    int rv;
    apr_off_t len = 0;
    int eos = 0;
    h2_headers *headers;
    
    ap_assert(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  H2_STRM_MSG(stream, "on_resume"));
    
send_headers:
    headers = NULL;
    status = h2_stream_out_prepare(stream, &len, &eos, &headers);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                  H2_STRM_MSG(stream, "prepared len=%ld, eos=%d"), 
                  (long)len, eos);
    if (headers) {
        status = on_stream_headers(session, stream, headers, len, eos);
        if (status != APR_SUCCESS || stream->rst_error) {
            return status;
        }
        goto send_headers;
    }
    else if (status != APR_EAGAIN) {
        /* we have DATA to send */
        if (!stream->has_response) {
            /* but no response */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                          H2_STRM_LOG(APLOGNO(03466), stream, 
                          "no response, RST_STREAM"));
            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
            return APR_SUCCESS;
        } 
        rv = nghttp2_session_resume_data(session->ngh2, stream->id);
        session->have_written = 1;
        ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                      APLOG_ERR : APLOG_DEBUG, 0, session->c,  
                      H2_STRM_LOG(APLOGNO(02936), stream, "resumed"));
    }
    return status;
}