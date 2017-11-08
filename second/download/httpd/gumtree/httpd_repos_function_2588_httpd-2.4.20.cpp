static int is_accepting_streams(h2_session *session)
{
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
        case H2_SESSION_ST_BUSY:
        case H2_SESSION_ST_WAIT:
            return 1;
        default:
            return 0;
    }
}