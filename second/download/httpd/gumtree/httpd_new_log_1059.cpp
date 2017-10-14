ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
                         "%s: apr_sockaddr_info_get() failed for %s",
                         ap_server_argv0, str);