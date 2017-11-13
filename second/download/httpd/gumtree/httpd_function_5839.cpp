static int on_frame_recv_cb(nghttp2_session *ng2s,
                            const nghttp2_frame *frame,
                            void *userp)
{
    h2_session *session = (h2_session *)userp;
    apr_status_t status = APR_SUCCESS;
    h2_stream *stream;
    
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): on_frame_rcv #%ld, type=%d", 
                  session->id, frame->hd.stream_id, 
                  (long)session->frames_received, frame->hd.type);

    ++session->frames_received;
    switch (frame->hd.type) {
        case NGHTTP2_HEADERS:
            /* This can be HEADERS for a new stream, defining the request,
             * or HEADER may come after DATA at the end of a stream as in
             * trailers */
            stream = h2_session_get_stream(session, frame->hd.stream_id);
            if (stream) {
                int eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
                
                if (h2_stream_is_scheduled(stream)) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                                  "h2_stream(%ld-%d): TRAILER, eos=%d", 
                                  session->id, frame->hd.stream_id, eos);
                    if (eos) {
                        status = h2_stream_close_input(stream);
                    }
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                                  "h2_stream(%ld-%d): HEADER, eos=%d", 
                                  session->id, frame->hd.stream_id, eos);
                    status = stream_schedule(session, stream, eos);
                }
            }
            else {
                status = APR_EINVAL;
            }
            break;
        case NGHTTP2_DATA:
            stream = h2_session_get_stream(session, frame->hd.stream_id);
            if (stream) {
                int eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                              "h2_stream(%ld-%d): DATA, len=%ld, eos=%d", 
                              session->id, frame->hd.stream_id, 
                              (long)frame->hd.length, eos);
                if (eos) {
                    status = h2_stream_close_input(stream);
                }
            }
            else {
                status = APR_EINVAL;
            }
            break;
        case NGHTTP2_PRIORITY:
            session->reprioritize = 1;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session:  stream(%ld-%d): PRIORITY frame "
                          " weight=%d, dependsOn=%d, exclusive=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->priority.pri_spec.weight,
                          frame->priority.pri_spec.stream_id,
                          frame->priority.pri_spec.exclusive);
            break;
        case NGHTTP2_WINDOW_UPDATE:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session:  stream(%ld-%d): WINDOW_UPDATE "
                          "incr=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->window_update.window_size_increment);
            break;
        default:
            if (APLOGctrace2(session->c)) {
                char buffer[256];
                
                frame_print(frame, buffer,
                            sizeof(buffer)/sizeof(buffer[0]));
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                              "h2_session: on_frame_rcv %s", buffer);
            }
            break;
    }

    if (status != APR_SUCCESS) {
        int rv;
        
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                      APLOGNO(02923) 
                      "h2_session: stream(%ld-%d): error handling frame",
                      session->id, (int)frame->hd.stream_id);
        rv = nghttp2_submit_rst_stream(ng2s, NGHTTP2_FLAG_NONE,
                                       frame->hd.stream_id,
                                       NGHTTP2_INTERNAL_ERROR);
        if (nghttp2_is_fatal(rv)) {
            return NGHTTP2_ERR_CALLBACK_FAILURE;
        }
    }
    
    return 0;
}