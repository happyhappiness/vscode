
static void h2_session_ev_pre_close(h2_session *session, int arg, const char *msg)
{
    h2_session_shutdown(session, arg, msg, 1);
}

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

static void h2_session_ev_stream_done(h2_session *session, int arg, const char *msg)
{
    --session->open_streams;
    switch (session->state) {
        case H2_SESSION_ST_IDLE:
            if (session->open_streams == 0) {
                /* enter keepalive timeout, since we no longer have streams */
                session->idle_until = (session->s->keep_alive_timeout
                                       + apr_time_now());
            }
            break;
        default:
            break;
    }
}

static void dispatch_event(h2_session *session, h2_session_event_t ev, 
                      int arg, const char *msg)
{
    switch (ev) {
