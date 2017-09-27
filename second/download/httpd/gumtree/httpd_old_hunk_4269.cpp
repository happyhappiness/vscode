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
                
