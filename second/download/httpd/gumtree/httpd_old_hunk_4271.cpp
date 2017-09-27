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
