static void ev_local_goaway(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            /* already did that? */
            break;
        case H2_PROXYS_ST_IDLE:
        case H2_PROXYS_ST_REMOTE_SHUTDOWN:
            /* all done */
            transit(session, "local goaway", H2_PROXYS_ST_DONE);
            break;
        default:
            transit(session, "local goaway", H2_PROXYS_ST_LOCAL_SHUTDOWN);
            break;
    }
}