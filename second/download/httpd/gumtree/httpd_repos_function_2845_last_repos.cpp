static void h2_session_ev_conn_error(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
        case H2_SESSION_ST_DONE:
            /* just leave */
            transit(session, "conn error", H2_SESSION_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                          H2_SSSN_LOG(APLOGNO(03401), session, 
                          "conn error -> shutdown"));
            h2_session_shutdown(session, arg, msg, 0);
            break;
    }
}