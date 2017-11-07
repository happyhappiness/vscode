ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00457)
                 "Accepting new connections again: "
                 "%u active conns (%u lingering/%u clogged/%u suspended), "
                 "%u idle workers",
                 apr_atomic_read32(&connection_count),
                 apr_atomic_read32(&lingering_count),
                 apr_atomic_read32(&clogged_count),
                 apr_atomic_read32(&suspended_count),
                 ap_queue_info_get_idlers(worker_queue_info));