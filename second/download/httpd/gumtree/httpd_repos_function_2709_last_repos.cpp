static void ev_conn_timeout(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
            transit(session, "conn timeout", H2_PROXYS_ST_DONE);
            break;
        default:
            session_shutdown(session, arg, msg);
            transit(session, "conn timeout", H2_PROXYS_ST_DONE);
            break;
    }
}