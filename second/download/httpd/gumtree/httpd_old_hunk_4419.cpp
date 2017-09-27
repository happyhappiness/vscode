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
