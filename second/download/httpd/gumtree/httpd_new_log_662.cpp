ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "%s: could not log pid to file %s",
                     ap_server_argv0, fname);