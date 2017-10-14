ap_log_perror(APLOG_MARK, APLOG_STARTUP | APLOG_WARNING, 0, a,
                     "%s: apr_gethostname() failed to determine ServerName",
                     ap_server_argv0);