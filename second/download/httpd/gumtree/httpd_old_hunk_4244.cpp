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
