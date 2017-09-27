                 }
                 break;
                 
             case H2_SESSION_ST_WAIT:
                 if (session->wait_us <= 0) {
                     session->wait_us = 10;
-                    session->start_wait = apr_time_now();
                     if (h2_conn_io_flush(&session->io) != APR_SUCCESS) {
                         dispatch_event(session, H2_SESSION_EV_CONN_ERROR, 0, NULL);
                         break;
                     }
                 }
-                else if ((apr_time_now() - session->start_wait) >= session->s->timeout) {
-                    /* waited long enough */
-                    if (trace) {
-                        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, APR_TIMEUP, c,
-                                      "h2_session: wait for data");
-                    }
-                    dispatch_event(session, H2_SESSION_EV_CONN_TIMEOUT, 0, "timeout");
-                    break;
-                }
                 else {
                     /* repeating, increase timer for graceful backoff */
                     session->wait_us = H2MIN(session->wait_us*2, MAX_WAIT_MICROS);
                 }
 
                 if (trace) {
