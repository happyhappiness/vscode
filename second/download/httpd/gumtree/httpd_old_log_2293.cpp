ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf,
                         "Parent: child process exited with status %lu -- Aborting.", exitcode);