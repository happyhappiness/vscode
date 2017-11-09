static apr_status_t session_start(h2_proxy_session *session) 
{
    nghttp2_settings_entry settings[2];
    int rv, add_conn_window;
    apr_socket_t *s;
    
    s = ap_get_conn_socket(session->c);
#if (!defined(WIN32) && !defined(NETWARE)) || defined(DOXYGEN)
    if (s) {
        ap_sock_disable_nagle(s);
    }
#endif
    
    settings[0].settings_id = NGHTTP2_SETTINGS_ENABLE_PUSH;
    settings[0].value = 0;
    settings[1].settings_id = NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE;
    settings[1].value = (1 << session->window_bits_stream) - 1;
    
    rv = nghttp2_submit_settings(session->ngh2, NGHTTP2_FLAG_NONE, settings, 
                                 H2_ALEN(settings));
    
    /* If the connection window is larger than our default, trigger a WINDOW_UPDATE */
    add_conn_window = ((1 << session->window_bits_connection) - 1 -
                       NGHTTP2_INITIAL_CONNECTION_WINDOW_SIZE);
    if (!rv && add_conn_window != 0) {
        rv = nghttp2_submit_window_update(session->ngh2, NGHTTP2_FLAG_NONE, 0, add_conn_window);
    }
    return rv? APR_EGENERAL : APR_SUCCESS;
}