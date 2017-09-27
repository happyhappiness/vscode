                             const nghttp2_frame *frame, void *user_data)
{
    h2_proxy_session *session = user_data;
    if (APLOGcdebug(session->c)) {
        char buffer[256];

        h2_proxy_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03343)
                      "h2_proxy_session(%s): sent FRAME[%s]",
                      session->id, buffer);
    }
    return 0;
}
