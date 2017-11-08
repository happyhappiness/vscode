static void ev_no_io(h2_proxy_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_PROXYS_ST_BUSY:
        case H2_PROXYS_ST_LOCAL_SHUTDOWN:
        case H2_PROXYS_ST_REMOTE_SHUTDOWN:
            /* nothing for input and output to do. If we remain
             * in this state, we go into a tight loop and suck up
             * CPU cycles. Ideally, we'd like to do a blocking read, but that
             * is not possible if we have scheduled tasks and wait
             * for them to produce something. */
            if (h2_proxy_ihash_empty(session->streams)) {
                if (!is_accepting_streams(session)) {
                    /* We are no longer accepting new streams and have
                     * finished processing existing ones. Time to leave. */
                    session_shutdown(session, arg, msg);
                    transit(session, "no io", H2_PROXYS_ST_DONE);
                }
                else {
                    /* When we have no streams, no task events are possible,
                     * switch to blocking reads */
                    transit(session, "no io", H2_PROXYS_ST_IDLE);
                }
            }
            else {
                /* Unable to do blocking reads, as we wait on events from
                 * task processing in other threads. Do a busy wait with
                 * backoff timer. */
                transit(session, "no io", H2_PROXYS_ST_WAIT);
            }
            break;
        default:
            /* nop */
            break;
    }
}