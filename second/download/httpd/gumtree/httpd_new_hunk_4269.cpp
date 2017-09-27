                        if (now > session->keep_sync_until) {
                            /* if we are on an async mpm, now is the time that
                             * we may dare to pass control to it. */
                            session->keep_sync_until = 0;
                        }
                        if (now > session->idle_until) {
                            if (trace) {
                                ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                              "h2_session(%ld): keepalive timeout",
                                              session->id);
                            }
                            dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
                        }
                        else if (trace) {                        
                            ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                          "h2_session(%ld): keepalive, %f sec left",
                                          session->id, (session->idle_until - now) / 1000000.0f);
                        }
                        /* continue reading handling */
                    }
                    else {
                        if (trace) {
                            ap_log_cerror( APLOG_MARK, APLOG_TRACE3, status, c,
                                          "h2_session(%ld): idle(1 sec timeout) "
                                          "read failed", session->id);
                        }
                        dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, "error");
                    }
                }
                
                break;
                
