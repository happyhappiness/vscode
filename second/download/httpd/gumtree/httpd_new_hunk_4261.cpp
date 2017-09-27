            return 1;
        default:
            return 0;
    }
}

static void update_child_status(h2_session *session, int status, const char *msg)
{
    /* Assume that we also change code/msg when something really happened and
     * avoid updating the scoreboard in between */
    if (session->last_status_code != status 
        || session->last_status_msg != msg) {
        apr_snprintf(session->status, sizeof(session->status),
                     "%s, streams: %d/%d/%d/%d/%d (open/recv/resp/push/rst)", 
                     msg? msg : "-",
                     (int)session->open_streams, 
                     (int)session->remote.emitted_count,
                     (int)session->responses_submitted,
                     (int)session->pushes_submitted,
                     (int)session->pushes_reset + session->streams_reset);
        ap_update_child_status_descr(session->c->sbh, status, session->status);
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
        }
    }
}

static void h2_session_ev_init(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
