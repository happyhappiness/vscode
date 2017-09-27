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
