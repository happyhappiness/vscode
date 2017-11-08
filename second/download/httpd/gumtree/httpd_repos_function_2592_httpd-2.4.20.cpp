static void h2_session_ev_remote_goaway(h2_session *session, int arg, const char *msg)
{
    session->remote.accepting = 0;
    cleanup_streams(session);
    switch (session->state) {
        case H2_SESSION_ST_REMOTE_SHUTDOWN:
            /* already received that? */
            break;
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* all done */
            transit(session, "remote goaway", H2_SESSION_ST_DONE);
            break;
        default:
            transit(session, "remote goaway", H2_SESSION_ST_REMOTE_SHUTDOWN);
            break;
    }
}