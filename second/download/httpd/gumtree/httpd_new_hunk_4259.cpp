    (void)prio;
    (void)valid_weight;
#endif
    return status;
}

int h2_session_push_enabled(h2_session *session)
{
    /* iff we can and they can and want */
    return (session->remote.accepting /* remote GOAWAY received */
            && h2_config_geti(session->config, H2_CONF_PUSH)
            && nghttp2_session_get_remote_settings(session->ngh2, 
