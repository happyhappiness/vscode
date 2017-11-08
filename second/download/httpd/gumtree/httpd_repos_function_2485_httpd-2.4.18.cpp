int h2_session_push_enabled(h2_session *session)
{
    return nghttp2_session_get_remote_settings(session->ngh2, 
                                               NGHTTP2_SETTINGS_ENABLE_PUSH);
}