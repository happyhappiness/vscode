static int on_frame_not_send_cb(nghttp2_session *ngh2,
                                const nghttp2_frame *frame,
                                int lib_error_code, void *userp)
{
    h2_session *session = (h2_session *)userp;
    (void)ngh2;
    
    if (APLOGctrace2(session->c)) {
        char buffer[256];
        
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session: callback on_frame_not_send error=%d %s",
                      lib_error_code, buffer);
    }
    return 0;
}