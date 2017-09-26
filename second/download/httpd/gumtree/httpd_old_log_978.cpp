ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: could not open document config file %s",
                     ap_server_argv0, fname);