ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                             "ap_queue_info_wait_for_idler failed.  "
                             "Attempting to shutdown process gracefully");