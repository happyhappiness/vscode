static void ev_proto_error(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_DONE:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            /* just leave */
            transit(session, "proto error", H2_PROXYS_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          "h2_proxy_session(%s): proto error -> shutdown", session->id);
            session_shutdown(session, arg, msg);
            break;
    }
}