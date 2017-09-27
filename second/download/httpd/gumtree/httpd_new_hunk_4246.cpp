                        void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream * stream;
    apr_status_t status;
    
    (void)flags;
    if (!is_accepting_streams(session)) {
        /* just ignore */
        return 0;
    }
    
    stream = get_stream(session, frame->hd.stream_id);
    if (!stream) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02920) 
                      "h2_session:  stream(%ld-%d): on_header unknown stream",
                      session->id, (int)frame->hd.stream_id);
        return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }
    
    status = h2_stream_add_header(stream, (const char *)name, namelen,
                                  (const char *)value, valuelen);
    if (status != APR_SUCCESS && !stream->response) {
        return NGHTTP2_ERR_TEMPORAL_CALLBACK_FAILURE;
    }
    return 0;
}

/**
