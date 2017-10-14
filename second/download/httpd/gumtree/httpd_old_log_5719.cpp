ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                             "All workers are busy, will close %d keep-alive "
                             "connections",
                             keepalive_q.count);