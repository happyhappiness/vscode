ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00457)
                 "Accepting new connections again: "
                 "%u active conns, %u idle workers",
                 apr_atomic_read32(&connection_count),
                 ap_queue_info_get_idlers(worker_queue_info));