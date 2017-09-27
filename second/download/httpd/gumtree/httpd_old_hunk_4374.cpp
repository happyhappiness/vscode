}

static int on_frame_recv(nghttp2_session *ngh2, const nghttp2_frame *frame,
                         void *user_data) 
{
    h2_proxy_session *session = user_data;
    int n;
    
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03341)
                      "h2_proxy_session(%s): recv FRAME[%s]",
                      session->id, buffer);
    }

    switch (frame->hd.type) {
        case NGHTTP2_HEADERS:
            break;
        case NGHTTP2_PUSH_PROMISE:
            break;
        case NGHTTP2_SETTINGS:
            if (frame->settings.niv > 0) {
                n = nghttp2_session_get_remote_settings(ngh2, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS);
