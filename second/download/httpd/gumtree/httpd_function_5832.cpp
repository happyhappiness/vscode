static int on_stream_close_cb(nghttp2_session *ngh2, int32_t stream_id,
                              uint32_t error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    h2_stream *stream;
    
    (void)ngh2;
    if (session->aborted) {
        return NGHTTP2_ERR_CALLBACK_FAILURE;
    }
    stream = h2_stream_set_get(session->streams, stream_id);
    if (stream) {
        stream_destroy(session, stream, error_code);
    }
    
    if (error_code) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): close error %d",
                      session->id, (int)stream_id, error_code);
    }
    
    return 0;
}