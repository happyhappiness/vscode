    if (status == APR_SUCCESS) {
        stream->out_data_frames++;
        stream->out_data_octets += length;
        return 0;
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,  
                      H2_STRM_LOG(APLOGNO(02925), stream, "failed send_data_cb"));
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
}

static int on_frame_send_cb(nghttp2_session *ngh2, 
                            const nghttp2_frame *frame,
                            void *user_data)
{
    h2_session *session = user_data;
    h2_stream *stream;
    int stream_id = frame->hd.stream_id;
    
    ++session->frames_sent;
    switch (frame->hd.type) {
        case NGHTTP2_PUSH_PROMISE:
            /* PUSH_PROMISE we report on the promised stream */
            stream_id = frame->push_promise.promised_stream_id;
            break;
        default:    
            break;
    }
    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03068), session, 
                      "sent FRAME[%s], frames=%ld/%ld (r/s)"),
                      buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }
    
    stream = h2_session_stream_get(session, stream_id);
    if (stream) {
        h2_stream_send_frame(stream, frame->hd.type, frame->hd.flags);
    }
    return 0;
}

#ifdef H2_NG2_INVALID_HEADER_CB
static int on_invalid_header_cb(nghttp2_session *ngh2, 
                                const nghttp2_frame *frame, 
                                const uint8_t *name, size_t namelen, 
                                const uint8_t *value, size_t valuelen, 
                                uint8_t flags, void *user_data)
{
    h2_session *session = user_data;
    h2_stream *stream;
    
    if (APLOGcdebug(session->c)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03456)
                      "h2_stream(%ld-%d): invalid header '%s: %s'", 
                      session->id, (int)frame->hd.stream_id,
                      apr_pstrndup(session->pool, (const char *)name, namelen),
                      apr_pstrndup(session->pool, (const char *)value, valuelen));
    }
    stream = h2_session_stream_get(session, frame->hd.stream_id);
    if (stream) {
        h2_stream_rst(stream, NGHTTP2_PROTOCOL_ERROR);
    }
    return 0;
}
#endif

#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

