    }
}

static void transit(h2_session *session, const char *action, h2_session_state nstate)
{
    if (session->state != nstate) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03078)
                      "h2_session(%ld): transit [%s] -- %s --> [%s]", session->id,
                      state_name(session->state), action, state_name(nstate));
        session->state = nstate;
        switch (session->state) {
            case H2_SESSION_ST_IDLE:
                update_child_status(session, (session->open_streams == 0? 
                                              SERVER_BUSY_KEEPALIVE
                                              : SERVER_BUSY_READ), "idle");
                break;
            case H2_SESSION_ST_REMOTE_SHUTDOWN:
                update_child_status(session, SERVER_CLOSING, "remote goaway");
                break;
            case H2_SESSION_ST_LOCAL_SHUTDOWN:
                update_child_status(session, SERVER_CLOSING, "local goaway");
                break;
            case H2_SESSION_ST_DONE:
                update_child_status(session, SERVER_CLOSING, "done");
                break;
            default:
                /* nop */
                break;
