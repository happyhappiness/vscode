                            void *user_data)
{
    h2_session *session = user_data;
    if (APLOGcdebug(session->c)) {
        char buffer[256];
        
        h2_util_frame_print(frame, buffer, sizeof(buffer)/sizeof(buffer[0]));
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03068)
                      "h2_session(%ld): sent FRAME[%s], frames=%ld/%ld (r/s)",
                      session->id, buffer, (long)session->frames_received,
                     (long)session->frames_sent);
    }
    ++session->frames_sent;
    return 0;
}

#define NGH2_SET_CALLBACK(callbacks, name, fn)\
nghttp2_session_callbacks_set_##name##_callback(callbacks, fn)

