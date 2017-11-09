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