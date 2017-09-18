ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_NOERRNO, 0, NULL,
                     "%s: bad group name %s", ap_server_argv0, name);