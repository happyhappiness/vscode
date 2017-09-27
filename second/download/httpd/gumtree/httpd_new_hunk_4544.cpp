 */
static int on_frame_recv_cb(nghttp2_session *ng2s,
                            const nghttp2_frame *frame,
                            void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03066), session, 
                      "recv FRAME[%s], frames=%ld/%ld (r/s)"),
                      buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }

    ++session->frames_received;
    switch (frame->hd.type) {
        case NGHTTP2_HEADERS:
            /* This can be HEADERS for a new stream, defining the request,
             * or HEADER may come after DATA at the end of a stream as in
             * trailers */
            stream = h2_session_stream_get(session, frame->hd.stream_id);
            if (stream) {
                h2_stream_recv_frame(stream, NGHTTP2_HEADERS, frame->hd.flags);
            }
            break;
        case NGHTTP2_DATA:
            stream = h2_session_stream_get(session, frame->hd.stream_id);
            if (stream) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,  
                              H2_STRM_LOG(APLOGNO(02923), stream, 
                              "DATA, len=%ld, flags=%d"), 
                              (long)frame->hd.length, frame->hd.flags);
                h2_stream_recv_frame(stream, NGHTTP2_DATA, frame->hd.flags);
            }
            break;
        case NGHTTP2_PRIORITY:
            session->reprioritize = 1;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_stream(%ld-%d): PRIORITY frame "
                          " weight=%d, dependsOn=%d, exclusive=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->priority.pri_spec.weight,
                          frame->priority.pri_spec.stream_id,
                          frame->priority.pri_spec.exclusive);
            break;
        case NGHTTP2_WINDOW_UPDATE:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_stream(%ld-%d): WINDOW_UPDATE incr=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->window_update.window_size_increment);
            break;
        case NGHTTP2_RST_STREAM:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03067)
                          "h2_stream(%ld-%d): RST_STREAM by client, errror=%d",
                          session->id, (int)frame->hd.stream_id,
                          (int)frame->rst_stream.error_code);
            stream = h2_session_stream_get(session, frame->hd.stream_id);
            if (stream && stream->initiated_on) {
                ++session->pushes_reset;
            }
            else {
                ++session->streams_reset;
            }
