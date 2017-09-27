            break;
    }
}

static void h2_session_ev_local_goaway(h2_session *session, int arg, const char *msg)
{
    cleanup_streams(session);
    if (!session->remote.shutdown) {
        update_child_status(session, SERVER_CLOSING, "local goaway");
    }
    transit(session, "local goaway", H2_SESSION_ST_DONE);
}

static void h2_session_ev_remote_goaway(h2_session *session, int arg, const char *msg)
{
    if (!session->remote.shutdown) {
        session->remote.error = arg;
        session->remote.accepting = 0;
        session->remote.shutdown = 1;
        cleanup_streams(session);
        update_child_status(session, SERVER_CLOSING, "remote goaway");
        transit(session, "remote goaway", H2_SESSION_ST_DONE);
    }
}

static void h2_session_ev_conn_error(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
        case H2_SESSION_ST_DONE:
            /* just leave */
            transit(session, "conn error", H2_SESSION_ST_DONE);
            break;
        
        default:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03401)
