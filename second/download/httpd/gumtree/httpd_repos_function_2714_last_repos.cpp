static void ev_data_read(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_IDLE:
        case H2_PROXYS_ST_WAIT:
            transit(session, "data read", H2_PROXYS_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}