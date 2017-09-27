    (void)ngh2;
    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03063), session, 
                      "recv invalid FRAME[%s], frames=%ld/%ld (r/s)"),
                      buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }
    return 0;
}

static int on_data_chunk_recv_cb(nghttp2_session *ngh2, uint8_t flags,
                                 int32_t stream_id,
                                 const uint8_t *data, size_t len, void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_EINVAL;
    h2_stream * stream;
    int rv = 0;
    
    stream = h2_session_stream_get(session, stream_id);
    if (stream) {
        status = h2_stream_recv_DATA(stream, flags, data, len);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03064)
                      "h2_stream(%ld-%d): on_data_chunk for unknown stream",
                      session->id, (int)stream_id);
        rv = NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    if (status != APR_SUCCESS) {
        /* count this as consumed explicitly as no one will read it */
        nghttp2_session_consume(session->ngh2, stream_id, len);
    }
    return rv;
}

static int on_stream_close_cb(nghttp2_session *ngh2, int32_t stream_id,
                              uint32_t error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    (void)ngh2;
    stream = h2_session_stream_get(session, stream_id);
    if (stream) {
        if (error_code) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          H2_STRM_LOG(APLOGNO(03065), stream, 
                          "closing with err=%d %s"), 
                          (int)error_code, h2_h2_err_description(error_code));
            h2_stream_rst(stream, error_code);
        }
    }
    return 0;
}

static int on_begin_headers_cb(nghttp2_session *ngh2,
                               const nghttp2_frame *frame, void *userp)
