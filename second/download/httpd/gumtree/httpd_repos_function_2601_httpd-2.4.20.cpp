static void h2_session_ev_pre_close(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            /* nop */
            break;
        default:
            h2_session_shutdown(session, arg, msg, 1);
            break;
    }
}