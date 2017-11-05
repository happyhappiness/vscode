ap_log_error(APLOG_MARK, APLOG_STARTUP, APR_EBADPATH, NULL,
                         "%s: Invalid error log path %s.",
                         ap_server_argv0, s->error_fname);