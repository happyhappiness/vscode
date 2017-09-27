ap_log_error(APLOG_MARK, APLOG_CRIT, ERROR_BAD_PATHNAME, ap_server_conf,
                         "Parent: Failed to get full path of %s",
                         ap_server_conf->process->argv[0]);