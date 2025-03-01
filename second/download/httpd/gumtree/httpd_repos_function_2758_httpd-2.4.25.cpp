static void h2_session_ev_stream_open(h2_session *session, int arg, const char *msg)
{
    ++session->open_streams;
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
            if (session->open_streams == 1) {
                /* enter tiomeout, since we have a stream again */
                session->idle_until = (session->s->timeout + apr_time_now());
            }
            break;
        default:
            break;
    }
}