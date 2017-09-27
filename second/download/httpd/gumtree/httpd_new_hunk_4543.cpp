{
    h2_session *session = (h2_session *)userp;
    h2_stream * stream;
    apr_status_t status;
    
    (void)flags;
    stream = h2_session_stream_get(session, frame->hd.stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(02920) 
                      "h2_stream(%ld-%d): on_header unknown stream",
                      session->id, (int)frame->hd.stream_id);
        return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }
    
    status = h2_stream_add_header(stream, (const char *)name, namelen,
                                  (const char *)value, valuelen);
    if (status != APR_SUCCESS && !h2_stream_is_ready(stream)) {
        return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }
    return 0;
}

/**
