ap_log_error(APLOG_MARK, APLOG_ERR, rv, ap_server_conf,
                                     "Child %d: Encountered too many accept() "
                                     "resource faults, aborting.",
                                     my_pid);