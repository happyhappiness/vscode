static void h2_session_ev_conn_error(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* just leave */
            transit(session, "conn error", H2_SESSION_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                          "h2_session(%ld): conn error -> shutdown", session->id);
            h2_session_shutdown(session, arg, msg, 0);
            break;
    }
}