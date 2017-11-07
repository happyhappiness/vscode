ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                                  "h2_session: wait for data, %ld micros", 
                                  (long)session->wait_us);