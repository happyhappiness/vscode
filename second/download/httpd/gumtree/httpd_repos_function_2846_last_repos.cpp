static void h2_session_ev_proto_error(h2_session *session, int arg, const char *msg)
{
    if (!session->local.shutdown) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_SSSN_LOG(APLOGNO(03402), session, 
                      "proto error -> shutdown"));
        h2_session_shutdown(session, arg, msg, 0);
    }
}