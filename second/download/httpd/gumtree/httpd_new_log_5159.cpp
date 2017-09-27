ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 "Too many open connections (%u), "
                                 "not accepting new conns in this process",
                                 apr_atomic_read32(&connection_count));