    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
    h2_stream * stream;
    int rv;
    
    (void)flags;
    if (!is_accepting_streams(session)) {
        /* ignore */
        return 0;
    }
    
    stream = h2_session_get_stream(session, stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03064)
                      "h2_stream(%ld-%d): on_data_chunk for unknown stream",
                      session->id, (int)stream_id);
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
        return 0;
    }

    /* FIXME: enabling setting EOS this way seems to break input handling
     * in mod_proxy_http2. why? */
    status = h2_stream_write_data(stream, (const char *)data, len,
                                  0 /*flags & NGHTTP2_FLAG_END_STREAM*/);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                  "h2_stream(%ld-%d): data_chunk_recv, written %ld bytes",
                  session->id, stream_id, (long)len);
    if (status != APR_SUCCESS) {
        update_window(session, stream_id, len);
        rv = nghttp2_submit_rst_stream(ngh2, NGHTTP2_FLAG_NONE, stream_id,
