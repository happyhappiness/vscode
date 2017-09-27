    if (status == APR_SUCCESS) {
        return length;
    }
    if (APR_STATUS_IS_EAGAIN(status)) {
        return NGHTTP2_ERR_WOULDBLOCK;
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session: send error");
    return h2_session_status_from_apr_status(status);
}

static int on_invalid_frame_recv_cb(nghttp2_session *ngh2,
                                    const nghttp2_frame *frame,
                                    int error, void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2;
    
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    if (APLOGctrace2(session->c)) {
        char buffer[256];
        
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                      "h2_session: callback on_invalid_frame_recv error=%d %s",
                      error, buffer);
    }
    return 0;
}

static int on_data_chunk_recv_cb(nghttp2_session *ngh2, uint8_t flags,
                                 int32_t stream_id,
