    h2_session *session = (h2_session *)userp;
    h2_stream * stream;
    apr_status_t status;
    
    (void)ngh2;
    (void)flags;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    stream = h2_session_get_stream(session, frame->hd.stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02920) 
