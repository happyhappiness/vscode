ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
                         apr_get_os_error(), NULL,
                         "OpenService failed");