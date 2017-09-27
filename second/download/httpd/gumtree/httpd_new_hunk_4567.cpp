                            /* if we are on an async mpm, now is the time that
                             * we may dare to pass control to it. */
                            session->keep_sync_until = 0;
                        }
                        if (now > session->idle_until) {
                            if (trace) {
                                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                              H2_SSSN_MSG(session, 
                                              "keepalive timeout"));
                            }
                            dispatch_event(session, 
                                           H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                        }
                        else if (trace) {                        
                            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, c,
                                          H2_SSSN_MSG(session, 
                                          "keepalive, %f sec left"),
                                          (session->idle_until - now) / 1000000.0f);
                        }
                        /* continue reading handling */
                    }
                    else if (APR_STATUS_IS_ECONNABORTED(status)
                             || APR_STATUS_IS_ECONNRESET(status)
                             || APR_STATUS_IS_EOF(status)
                             || APR_STATUS_IS_EBADF(status)) {
                        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                      H2_SSSN_MSG(session, "input gone"));
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                    }
                    else {
                        ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                      H2_SSSN_MSG(session, 
                                      "(1 sec timeout) read failed"));
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "error");
                    }
                }
                break;
                
            case H2_SESSION_ST_BUSY:
                if (nghttp2_session_want_read(session->ngh2)) {
                    ap_update_child_status(session->c->sbh, SERVER_BUSY_READ, NULL);
                    h2_filter_cin_timeout_set(session->cin, session->s->timeout);
