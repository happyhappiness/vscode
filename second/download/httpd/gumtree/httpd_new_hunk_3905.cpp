                                "FRAME[type=%d, length=%d, flags=%d, stream=%d]",
                                frame->hd.type, (int)frame->hd.length,
                                frame->hd.flags, frame->hd.stream_id);
    }
}

int h2_session_push_enabled(h2_session *session)
{
    return nghttp2_session_get_remote_settings(session->ngh2, 
                                               NGHTTP2_SETTINGS_ENABLE_PUSH);
}


apr_status_t h2_session_process(h2_session *session)
{
    apr_status_t status = APR_SUCCESS;
    apr_interval_time_t wait_micros = 0;
    static const int MAX_WAIT_MICROS = 200 * 1000;
    int got_streams = 0;
    h2_stream *stream;

    while (!session->aborted && (nghttp2_session_want_read(session->ngh2)
                                 || nghttp2_session_want_write(session->ngh2))) {
        int have_written = 0;
        int have_read = 0;
                                 
        got_streams = !h2_stream_set_is_empty(session->streams);
        if (got_streams) {            
            h2_session_resume_streams_with_data(session);
            
            if (h2_stream_set_has_unsubmitted(session->streams)) {
                int unsent_submits = 0;
                
                /* If we have responses ready, submit them now. */
                while ((stream = h2_mplx_next_submit(session->mplx, session->streams))) {
                    status = submit_response(session, stream);
                    ++unsent_submits;
                    
                    /* Unsent push promises are written immediately, as nghttp2
                     * 1.5.0 realizes internal stream data structures only on 
                     * send and we might need them for other submits. 
                     * Also, to conserve memory, we send at least every 10 submits
                     * so that nghttp2 does not buffer all outbound items too 
                     * long.
                     */
                    if (status == APR_SUCCESS 
                        && (session->unsent_promises || unsent_submits > 10)) {
                        int rv = nghttp2_session_send(session->ngh2);
                        if (rv != 0) {
                            ap_log_cerror( APLOG_MARK, APLOG_DEBUG, 0, session->c,
                                          "h2_session: send: %s", nghttp2_strerror(rv));
                            if (nghttp2_is_fatal(rv)) {
                                h2_session_abort(session, status, rv);
                                goto end_process;
                            }
                        }
                        else {
                            have_written = 1;
                            wait_micros = 0;
                            session->unsent_promises = 0;
                            unsent_submits = 0;
                        }
                    }
                }
            }
        }
        
        /* Send data as long as we have it and window sizes allow. We are
         * a server after all.
         */
        if (nghttp2_session_want_write(session->ngh2)) {
            int rv;
            
            rv = nghttp2_session_send(session->ngh2);
            if (rv != 0) {
                ap_log_cerror( APLOG_MARK, APLOG_DEBUG, 0, session->c,
                              "h2_session: send: %s", nghttp2_strerror(rv));
                if (nghttp2_is_fatal(rv)) {
                    h2_session_abort(session, status, rv);
                    goto end_process;
                }
            }
            else {
                have_written = 1;
                wait_micros = 0;
                session->unsent_promises = 0;
            }
        }
        
        if (wait_micros > 0) {
            if (APLOGcdebug(session->c)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                              "h2_session: wait for data, %ld micros", 
                              (long)wait_micros);
            }
            nghttp2_session_send(session->ngh2);
            h2_conn_io_flush(&session->io);
            status = h2_mplx_out_trywait(session->mplx, wait_micros, session->iowait);
            
            if (status == APR_TIMEUP) {
                if (wait_micros < MAX_WAIT_MICROS) {
                    wait_micros *= 2;
                }
            }
        }
        
        if (nghttp2_session_want_read(session->ngh2))
        {
            /* When we
             * - and have no streams at all
             * - or have streams, but none is suspended or needs submit and
             *   have nothing written on the last try
             * 
             * or, the other way around
             * - have only streams where data can be sent, but could
             *   not send anything
             *
             * then we are waiting on frames from the client (for
             * example WINDOW_UPDATE or HEADER) and without new frames
             * from the client, we cannot make any progress,
             * 
             * and *then* we can safely do a blocking read.
             */
            int may_block = (session->frames_received <= 1);
            if (!may_block) {
                if (got_streams) {
                    may_block = (!have_written 
                                 && !h2_stream_set_has_unsubmitted(session->streams)
                                 && !h2_stream_set_has_suspended(session->streams));
                }
                else {
                    may_block = 1;
                }
            }
            
            if (may_block) {
                h2_conn_io_flush(&session->io);
                if (session->c->cs) {
                    session->c->cs->state = (got_streams? CONN_STATE_HANDLER
                                             : CONN_STATE_WRITE_COMPLETION);
                }
                status = h2_conn_io_read(&session->io, APR_BLOCK_READ, 
                                         session_receive, session);
            }
            else {
                if (session->c->cs) {
                    session->c->cs->state = CONN_STATE_HANDLER;
                }
                status = h2_conn_io_read(&session->io, APR_NONBLOCK_READ, 
                                         session_receive, session);
            }

            switch (status) {
                case APR_SUCCESS:       /* successful read, reset our idle timers */
                    have_read = 1;
                    wait_micros = 0;
                    break;
                case APR_EAGAIN:              /* non-blocking read, nothing there */
                    break;
                default:
                    if (APR_STATUS_IS_ETIMEDOUT(status)
                        || APR_STATUS_IS_ECONNABORTED(status)
                        || APR_STATUS_IS_ECONNRESET(status)
                        || APR_STATUS_IS_EOF(status)
                        || APR_STATUS_IS_EBADF(status)) {
                        /* common status for a client that has left */
                        ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, session->c,
                                      "h2_session(%ld): terminating",
                                      session->id);
                        /* Stolen from mod_reqtimeout to speed up lingering when
                         * a read timeout happened.
                         */
                        apr_table_setn(session->c->notes, "short-lingering-close", "1");
                    }
                    else {
                        /* uncommon status, log on INFO so that we see this */
                        ap_log_cerror( APLOG_MARK, APLOG_INFO, status, session->c,
                                      APLOGNO(02950) 
                                      "h2_session(%ld): error reading, terminating",
                                      session->id);
                    }
                    h2_session_abort(session, status, 0);
                    goto end_process;
            }
        }
        
        got_streams = !h2_stream_set_is_empty(session->streams);
        if (got_streams) {            
            if (session->reprioritize) {
                h2_mplx_reprioritize(session->mplx, stream_pri_cmp, session);
                session->reprioritize = 0;
            }
            
            if (!have_read && !have_written) {
                /* Nothing read or written. That means no data yet ready to 
                 * be send out. Slowly back off...
                 */
                if (wait_micros == 0) {
                    wait_micros = 10;
                }
            }
            
            /* Check that any pending window updates are sent. */
            status = h2_mplx_in_update_windows(session->mplx);
            if (APR_STATUS_IS_EAGAIN(status)) {
                status = APR_SUCCESS;
            }
            else if (status == APR_SUCCESS) {
                /* need to flush window updates onto the connection asap */
                h2_conn_io_flush(&session->io);
            }
        }
        
        if (have_written) {
            h2_conn_io_flush(&session->io);
        }
    }
    
end_process:
    return status;
}
