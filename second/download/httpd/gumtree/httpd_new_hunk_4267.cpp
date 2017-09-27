                    }
                    dispatch_event(session, H2_SESSION_EV_INIT, 0, NULL);
                }
                break;
                
            case H2_SESSION_ST_IDLE:
                /* make certain, we send everything before we idle */
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
