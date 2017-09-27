            break;
    }
}

static void h2_session_ev_proto_error(h2_session *session, int arg, const char *msg)
{
    if (!session->local.shutdown) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03402)
                      "h2_session(%ld): proto error -> shutdown", session->id);
        h2_session_shutdown(session, arg, msg, 0);
    }
}

static void h2_session_ev_conn_timeout(h2_session *session, int arg, const char *msg)
{
    transit(session, msg, H2_SESSION_ST_DONE);
    if (!session->local.shutdown) {
        h2_session_shutdown(session, arg, msg, 1);
    }
}

static void h2_session_ev_no_io(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_BUSY:
            /* Nothing to READ, nothing to WRITE on the master connection.
             * Possible causes:
             * - we wait for the client to send us sth
             * - we wait for started tasks to produce output
             * - we have finished all streams and the client has sent GO_AWAY
             */
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session(%ld): NO_IO event, %d streams open", 
                          session->id, session->open_streams);
            h2_conn_io_flush(&session->io);
            if (session->open_streams > 0) {
                if (h2_mplx_awaits_data(session->mplx)) {
                    /* waiting for at least one stream to produce data */
                    transit(session, "no io", H2_SESSION_ST_WAIT);
                }
                else {
                    /* we have streams open, and all are submitted and none
                     * is suspended. The only thing keeping us from WRITEing
