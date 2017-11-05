ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(),
                         ap_server_conf, APLOGNO(00356)
                         "Child: WAIT_FAILED -- shutting down server");