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
