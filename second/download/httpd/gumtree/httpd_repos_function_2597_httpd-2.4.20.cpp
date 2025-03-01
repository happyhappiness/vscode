static void h2_session_ev_stream_ready(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_WAIT:
            transit(session, "stream ready", H2_SESSION_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}