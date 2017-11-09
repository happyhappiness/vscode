static void ev_remote_goaway(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_REMOTE_SHUTDOWN:
            /* already received that? */
            break;
        case H2_PROXYS_ST_IDLE:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            /* all done */
            transit(session, "remote goaway", H2_PROXYS_ST_DONE);
            break;
        default:
            transit(session, "remote goaway", H2_PROXYS_ST_REMOTE_SHUTDOWN);
            break;
    }
}