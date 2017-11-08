static void ev_stream_resumed(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_WAIT:
            transit(session, "stream resumed", H2_PROXYS_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}