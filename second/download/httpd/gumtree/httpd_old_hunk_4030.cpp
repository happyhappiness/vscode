                            void *user_data)
{
    h2_session *session = user_data;
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_session(%ld): frame_send %s",
                      session->id, buffer);
    }
    return 0;
}

#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

