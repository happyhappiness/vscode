ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                              "h2_session: wait for data, %ld micros", 
                              (long)wait_micros);