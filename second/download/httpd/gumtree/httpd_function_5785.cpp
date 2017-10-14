apr_status_t h2_session_process(h2_session *session)
{
    apr_status_t status = APR_SUCCESS;
    int rv = 0;
    apr_interval_time_t wait_micros = 0;
    static const int MAX_WAIT_MICROS = 200 * 1000;
    
    /* Start talking to the client. Apart from protocol meta data,
     * we mainly will see new http/2 streams opened by the client, which
     * basically are http requests we need to dispatch.
     *
     * There will be bursts of new streams, to be served concurrently,
     * followed by long pauses of no activity.
     *
     * Since the purpose of http/2 is to allow siumultaneous streams, we
     * need to dispatch the handling of each stream into a separate worker
     * thread, keeping this thread open for sending responses back as
     * soon as they arrive.
     * At the same time, we need to continue reading new frames from
     * our client, which may be meta (WINDOWS_UPDATEs, PING, SETTINGS) or
     * new streams.
     *
     * As long as we have streams open in this session, we cannot really rest
     * since there are two conditions to wait on: 1. new data from the client,
     * 2. new data from the open streams to send back.
     *
     * Only when we have no more streams open, can we do a blocking read
     * on our connection.
     *
     * TODO: implement graceful GO_AWAY after configurable idle time
     */
    
    ap_update_child_status_from_conn(session->c->sbh, SERVER_BUSY_READ, 
                                     session->c);

    if (APLOGctrace2(session->c)) {
        ap_filter_t *filter = session->c->input_filters;
        while (filter) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_conn(%ld), has connection filter %s",
                          session->id, filter->frec->name);
            filter = filter->next;
        }
    }
    
    status = h2_session_start(session, &rv);
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): starting on %s:%d", session->id,
                  session->c->base_server->defn_name,
                  session->c->local_addr->port);
    if (status != APR_SUCCESS) {
        h2_session_abort(session, status, rv);
        h2_session_destroy(session);
        return status;
    }
    
    while (!h2_session_is_done(session)) {
        int have_written = 0;
        int have_read = 0;
        int got_streams;
        
        status = h2_session_write(session, wait_micros);
        if (status == APR_SUCCESS) {
            have_written = 1;
            wait_micros = 0;
        }
        else if (status == APR_EAGAIN) {
            /* nop */
        }
        else if (status == APR_TIMEUP) {
            wait_micros *= 2;
            if (wait_micros > MAX_WAIT_MICROS) {
                wait_micros = MAX_WAIT_MICROS;
            }
        }
        else {
            ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                          "h2_session(%ld): writing, terminating",
                          session->id);
            h2_session_abort(session, status, 0);
            break;
        }
        
        /* We would like to do blocking reads as often as possible as they
         * are more efficient in regard to server resources.
         * We can do them under the following circumstances:
         * - we have no open streams and therefore have nothing to write
         * - we have just started the session and are waiting for the first
         *   two frames to come in. There will always be at least 2 frames as
         *   * h2 will send SETTINGS and SETTINGS-ACK
         *   * h2c will count the header settings as one frame and we
         *     submit our settings and need the ACK.
         */
        got_streams = !h2_stream_set_is_empty(session->streams);
        status = h2_session_read(session, 
                                 (!got_streams 
                                  || session->frames_received <= 1)?
                                 APR_BLOCK_READ : APR_NONBLOCK_READ);
        switch (status) {
            case APR_SUCCESS:       /* successful read, reset our idle timers */
                have_read = 1;
                wait_micros = 0;
                break;
            case APR_EAGAIN:              /* non-blocking read, nothing there */
                break;
            case APR_EBADF:               /* connection is not there any more */
            case APR_EOF:
            case APR_ECONNABORTED:
            case APR_ECONNRESET:
            case APR_TIMEUP:                       /* blocked read, timed out */
                ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                              "h2_session(%ld): reading",
                              session->id);
                h2_session_abort(session, status, 0);
                break;
            default:
                ap_log_cerror( APLOG_MARK, APLOG_INFO, status, session->c,
                              APLOGNO(02950) 
                              "h2_session(%ld): error reading, terminating",
                              session->id);
                h2_session_abort(session, status, 0);
                break;
        }
        
        if (!have_read && !have_written
            && !h2_stream_set_is_empty(session->streams)) {
            /* Nothing to read or write, we have streams, but
             * the have no data yet ready to be delivered. Slowly
             * back off to give others a chance to do their work.
             */
            if (wait_micros == 0) {
                wait_micros = 10;
            }
        }
    }
    
    ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                  "h2_session(%ld): done", session->id);
    
    ap_update_child_status_from_conn(session->c->sbh, SERVER_CLOSING, 
                                     session->c);

    h2_session_close(session);
    h2_session_destroy(session);
    
    return DONE;
}