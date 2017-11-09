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