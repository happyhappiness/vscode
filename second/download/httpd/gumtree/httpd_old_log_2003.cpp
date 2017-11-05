ap_log_error(APLOG_MARK,APLOG_ERR, rv, ap_server_conf,
                         "%s child %lu: Unable to init the start_mutex.",
                         service_name, my_pid);