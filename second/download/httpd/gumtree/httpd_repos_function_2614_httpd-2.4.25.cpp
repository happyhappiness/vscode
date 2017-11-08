static int is_accepting_streams(h2_proxy_session *session)
{
    switch (session->state) {
        case H2_PROXYS_ST_IDLE:
        case H2_PROXYS_ST_BUSY:
        case H2_PROXYS_ST_WAIT:
            return 1;
        default:
            return 0;
    }
}