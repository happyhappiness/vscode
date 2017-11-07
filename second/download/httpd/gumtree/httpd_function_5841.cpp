apr_status_t h2_session_process(h2_session *session, int async)
{
    apr_status_t status = APR_SUCCESS;
    conn_rec *c = session->c;
    int rv, have_written, have_read, mpm_state, no_streams;

    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_session(%ld): process start, async=%d", session->id, async);
                  
    if (c->cs) {
        c->cs->state = CONN_STATE_WRITE_COMPLETION;
    }
    
    while (1) {
        have_read = have_written = 0;

        if (!ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state)) {
            if (mpm_state == AP_MPMQ_STOPPING) {
                dispatch_event(session, H2_SESSION_EV_MPM_STOPPING, 0, NULL);
                break;
            }
        }
        
        session->status[0] = '\0';
        
        switch (session->state) {
            case H2_SESSION_ST_INIT:
                ap_update_child_status_from_conn(c->sbh, SERVER_BUSY_READ, c);
                if (!h2_is_acceptable_connection(c, 1)) {
                    update_child_status(session, SERVER_BUSY_READ, "inadequate security");
                    h2_session_shutdown(session, NGHTTP2_INADEQUATE_SECURITY, NULL, 1);
                } 
                else {
                    update_child_status(session, SERVER_BUSY_READ, "init");
                    status = h2_session_start(session, &rv);
                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c, APLOGNO(03079)
                                  "h2_session(%ld): started on %s:%d", session->id,
                                  session->s->server_hostname,
                                  c->local_addr->port);
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                    dispatch_event(session, H2_SESSION_EV_INIT, 0, NULL);
                }
                break;
                
            case H2_SESSION_ST_IDLE:
                no_streams = h2_ihash_is_empty(session->streams);
                update_child_status(session, (no_streams? SERVER_BUSY_KEEPALIVE
                                              : SERVER_BUSY_READ), "idle");
                /* make certain, the client receives everything before we idle */
                if (!session->keep_sync_until 
                    && async && no_streams && !session->r && session->remote.emitted_count) {
                    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                                  "h2_session(%ld): async idle, nonblock read", session->id);
                    /* We do not return to the async mpm immediately, since under
                     * load, mpms show the tendency to throw keep_alive connections
                     * away very rapidly.
                     * So, if we are still processing streams, we wait for the
                     * normal timeout first and, on timeout, close.
                     * If we have no streams, we still wait a short amount of
                     * time here for the next frame to arrive, before handing
                     * it to keep_alive processing of the mpm.
                     */
                    status = h2_session_read(session, 0);
                    
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (APR_STATUS_IS_EAGAIN(status) || APR_STATUS_IS_TIMEUP(status)) {
                        if (apr_time_now() > session->idle_until) {
                            dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, NULL);
                        }
                        else {
                            status = APR_EAGAIN;
                            goto out;
                        }
                    }
                    else {
                        ap_log_cerror( APLOG_MARK, APLOG_DEBUG, status, c,
                                      "h2_session(%ld): idle, no data, error", 
                                      session->id);
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "timeout");
                    }
                }
                else {
                    /* We wait in smaller increments, using a 1 second timeout.
                     * That gives us the chance to check for MPMQ_STOPPING often. 
                     */
                    status = h2_mplx_idle(session->mplx);
                    if (status != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                       H2_ERR_ENHANCE_YOUR_CALM, "less is more");
                    }
                    h2_filter_cin_timeout_set(session->cin, apr_time_from_sec(1));
                    status = h2_session_read(session, 1);
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (status == APR_EAGAIN) {
                        /* nothing to read */
                    }
                    else if (APR_STATUS_IS_TIMEUP(status)) {
                        apr_time_t now = apr_time_now();
                        if (now > session->keep_sync_until) {
                            /* if we are on an async mpm, now is the time that
                             * we may dare to pass control to it. */
                            session->keep_sync_until = 0;
                        }
                        if (now > session->idle_until) {
                            dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                        }
                        /* continue reading handling */
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "error");
                    }
                }
                
                break;
                
            case H2_SESSION_ST_BUSY:
            case H2_SESSION_ST_LOCAL_SHUTDOWN:
            case H2_SESSION_ST_REMOTE_SHUTDOWN:
                if (nghttp2_session_want_read(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_READ, NULL);
                    h2_filter_cin_timeout_set(session->cin, session->s->timeout);
                    status = h2_session_read(session, 0);
                    if (status == APR_SUCCESS) {
                        have_read = 1;
                        update_child_status(session, SERVER_BUSY_READ, "busy");
                        dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                    }
                    else if (status == APR_EAGAIN) {
                        /* nothing to read */
                    }
                    else if (APR_STATUS_IS_TIMEUP(status)) {
                        dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, NULL);
                        break;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                }
                
                if (!h2_ihash_is_empty(session->streams)) {
                    /* resume any streams for which data is available again */
                    h2_session_resume_streams_with_data(session);
                    /* Submit any responses/push_promises that are ready */
                    status = h2_session_submit(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else if (status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "submit error");
                        break;
                    }
                    /* send out window updates for our inputs */
                    status = h2_mplx_in_update_windows(session->mplx);
                    if (status != APR_SUCCESS && status != APR_EAGAIN) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "window update error");
                        break;
                    }
                }
                
                if (nghttp2_session_want_write(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_WRITE, NULL);
                    status = h2_session_send(session);
                    if (status == APR_SUCCESS) {
                        have_written = 1;
                    }
                    else {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 
                                         H2_ERR_INTERNAL_ERROR, "writing");
                        break;
                    }
                }
                
                if (have_read || have_written) {
                    if (session->wait_us) {
                        session->wait_us = 0;
                    }
                }
                else if (!nghttp2_session_want_write(session->ngh2)) {
                    dispatch_event(session, H2_SESSION_EV_NO_IO, 0, NULL);
                }
                break;
                
            case H2_SESSION_ST_WAIT:
                if (session->wait_us <= 0) {
                    session->wait_us = 10;
                    session->start_wait = apr_time_now();
                    if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                    update_child_status(session, SERVER_BUSY_READ, "wait");
                }
                else if ((apr_time_now() - session->start_wait) >= session->s->timeout) {
                    /* waited long enough */
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, APR_TIMEUP, c,
                                  "h2_session: wait for data");
                    dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                    break;
                }
                else {
                    /* repeating, increase timer for graceful backoff */
                    session->wait_us = H2MIN(session->wait_us*2, MAX_WAIT_MICROS);
                }

                if (APLOGctrace1(c)) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                                  "h2_session: wait for data, %ld micros", 
                                  (long)session->wait_us);
                }
                status = h2_mplx_out_trywait(session->mplx, session->wait_us, 
                                             session->iowait);
                if (status == APR_SUCCESS) {
                    session->wait_us = 0;
                    dispatch_event(session, H2_SESSION_EV_DATA_READ, 0, NULL);
                }
                else if (status == APR_TIMEUP) {
                    /* go back to checking all inputs again */
                    transit(session, "wait cycle", session->local.accepting? 
                            H2_SESSION_ST_BUSY : H2_SESSION_ST_LOCAL_SHUTDOWN);
                }
                else {
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, c,
                                  "h2_session(%ld): waiting on conditional",
                                  session->id);
                    h2_session_shutdown(session, H2_ERR_INTERNAL_ERROR, 
                                        "cond wait error", 0);
                }
                break;
                
            case H2_SESSION_ST_DONE:
                update_child_status(session, SERVER_CLOSING, "done");
                status = APR_EOF;
                goto out;
                
            default:
                ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
                              APLOGNO(03080)
                              "h2_session(%ld): unknown state %d", session->id, session->state);
                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, 0, NULL);
                break;
        }

        if (!nghttp2_session_want_read(session->ngh2) 
                 && !nghttp2_session_want_write(session->ngh2)) {
            dispatch_event(session, H2_SESSION_EV_NGH2_DONE, 0, NULL); 
        }
        if (session->reprioritize) {
            h2_mplx_reprioritize(session->mplx, stream_pri_cmp, session);
            session->reprioritize = 0;
        }
    }
    
out:
    ap_log_cerror( APLOG_MARK, APLOG_TRACE1, status, c,
                  "h2_session(%ld): [%s] process returns", 
                  session->id, state_name(session->state));

    if ((session->state != H2_SESSION_ST_DONE)
        && (APR_STATUS_IS_EOF(status)
            || APR_STATUS_IS_ECONNRESET(status) 
            || APR_STATUS_IS_ECONNABORTED(status))) {
            dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
        }

    status = (session->state == H2_SESSION_ST_DONE)? APR_EOF : APR_SUCCESS;
    if (session->state == H2_SESSION_ST_DONE) {
        if (!session->eoc_written) {
            session->eoc_written = 1;
            h2_conn_io_write_eoc(&session->io, session);
        }
    }
    
    return status;
}