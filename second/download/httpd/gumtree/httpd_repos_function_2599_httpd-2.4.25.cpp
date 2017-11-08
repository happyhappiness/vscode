static int on_stream_close(nghttp2_session *ngh2, int32_t stream_id,
                           uint32_t error_code, void *user_data) 
{
    h2_proxy_session *session = user_data;
    h2_proxy_stream *stream;
    if (!session->aborted) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03360)
                      "h2_proxy_session(%s): stream=%d, closed, err=%d", 
                      session->id, stream_id, error_code);
        stream = h2_proxy_ihash_get(session->streams, stream_id);
        if (stream) {
            stream->error_code = error_code;
        }
        dispatch_event(session, H2_PROXYS_EV_STREAM_DONE, stream_id, NULL);
    }
    return 0;
}