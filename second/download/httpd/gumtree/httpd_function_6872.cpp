static void transit(h2_session *session, const char *action, h2_session_state nstate)
{
    if (session->state != nstate) {
        int loglvl = APLOG_DEBUG;
        if ((session->state == H2_SESSION_ST_BUSY && nstate == H2_SESSION_ST_WAIT)
            || (session->state == H2_SESSION_ST_WAIT && nstate == H2_SESSION_ST_BUSY)){
            loglvl = APLOG_TRACE1;
        }
        ap_log_cerror(APLOG_MARK, loglvl, 0, session->c, APLOGNO(03078)
                      "h2_session(%ld): transit [%s] -- %s --> [%s]", session->id,
                      state_name(session->state), action, state_name(nstate));
        session->state = nstate;
        switch (session->state) {
            case H2_SESSION_ST_IDLE:
                update_child_status(session, (session->open_streams == 0? 
                                              SERVER_BUSY_KEEPALIVE
                                              : SERVER_BUSY_READ), "idle");
                break;
            case H2_SESSION_ST_DONE:
                update_child_status(session, SERVER_CLOSING, "done");
                break;
            default:
                /* nop */
                break;
        }
    }
}