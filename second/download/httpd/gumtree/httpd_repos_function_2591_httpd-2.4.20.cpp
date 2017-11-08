static void h2_session_ev_local_goaway(h2_session *session, int arg, const char *msg)
{
    session->local.accepting = 0;
    cleanup_streams(session);
    switch (session->state) {
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* already did that? */
            break;
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_REMOTE_SHUTDOWN:
            /* all done */
            transit(session, "local goaway", H2_SESSION_ST_DONE);
            break;
        default:
            transit(session, "local goaway", H2_SESSION_ST_LOCAL_SHUTDOWN);
            break;
    }
}