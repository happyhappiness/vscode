static void h2_session_ev_conn_timeout(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_LOCAL_SHUTDOWN:
            transit(session, "conn timeout", H2_SESSION_ST_DONE);
            break;
        default:
            h2_session_shutdown(session, arg, msg, 1);
            transit(session, "conn timeout", H2_SESSION_ST_DONE);
            break;
    }
}