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
                /* make certain, we send everything before we idle */
                h2_conn_io_flush(&session->io);
                if (!session->keep_sync_until && async && !session->open_streams
                    && !session->r && session->remote.emitted_count) {
                    if (trace) {
                        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                      "h2_session(%ld): async idle, nonblock read, "
                                      "%d streams open", session->id, 
                                      session->open_streams);
                    }
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
                        session->have_read = 1;
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
				      APLOGNO(03403)
                                      "h2_session(%ld): idle, no data, error", 
                                      session->id);
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "timeout");
                    }
                }
                else {
                    if (trace) {
                        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                      "h2_session(%ld): sync idle, stutter 1-sec, "
                                      "%d streams open", session->id,
                                      session->open_streams);
                    }
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
