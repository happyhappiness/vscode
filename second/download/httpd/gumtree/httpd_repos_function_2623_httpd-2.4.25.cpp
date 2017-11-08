static void ev_stream_submitted(h2_proxy_session *session, int stream_id, 
                                const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_IDLE:
        case H2_PROXYS_ST_WAIT:
            transit(session, "stream submitted", H2_PROXYS_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}