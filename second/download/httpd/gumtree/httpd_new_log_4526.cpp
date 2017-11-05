ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, ap_server_conf,
                                 "Idle workers: %u",
                                 ap_queue_info_get_idlers(worker_queue_info));