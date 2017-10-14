ap_log_error(APLOG_MARK, APLOG_TRACE6, 0, ap_server_conf,
                             "connections: %d (write-completion: %d "
                             "keep-alive: %d lingering: %d)",
                             connection_count, write_completion_q.count,
                             keepalive_q.count,
                             linger_q.count + short_linger_q.count);