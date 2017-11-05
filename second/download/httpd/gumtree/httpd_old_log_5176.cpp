ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                             "connections: %u (clogged: %u write-completion: %d "
                             "keep-alive: %d lingering: %d suspended: %u)",
                             apr_atomic_read32(&connection_count),
                             apr_atomic_read32(&clogged_count),
                             write_completion_q.count,
                             keepalive_q.count,
                             apr_atomic_read32(&lingering_count),
                             apr_atomic_read32(&suspended_count));