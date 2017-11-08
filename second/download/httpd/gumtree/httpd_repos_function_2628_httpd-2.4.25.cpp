static void ev_pre_close(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_DONE:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            /* nop */
            break;
        default:
            session_shutdown(session, arg, msg);
            break;
    }
}