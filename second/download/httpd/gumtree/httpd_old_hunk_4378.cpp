    h2_proxy_session *session = user_data;
    h2_proxy_stream *stream;
    if (!session->aborted) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03360)
                      "h2_proxy_session(%s): stream=%d, closed, err=%d", 
                      session->id, stream_id, error_code);
        stream = h2_ihash_get(session->streams, stream_id);
        if (stream) {
            stream->error_code = error_code;
        }
        dispatch_event(session, H2_PROXYS_EV_STREAM_DONE, stream_id, NULL);
    }
    return 0;
