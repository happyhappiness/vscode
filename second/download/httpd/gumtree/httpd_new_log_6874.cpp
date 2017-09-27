ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                                 "%u/%u workers shutdown",
                                 apr_atomic_read32(&threads_shutdown),
                                 threads_per_child);