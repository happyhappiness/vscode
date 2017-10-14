static int send_loop(h2_proxy_session *session)
{
    while (nghttp2_session_want_write(session->ngh2)) {
        int rv = nghttp2_session_send(session->ngh2);
        if (rv < 0 && nghttp2_is_fatal(rv)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                          "h2_proxy_session(%s): write, rv=%d", session->id, rv);
            dispatch_event(session, H2_PROXYS_EV_CONN_ERROR, rv, NULL);
            break;
        }
        return 1;
    }
    return 0;
}