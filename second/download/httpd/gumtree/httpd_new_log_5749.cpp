ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                         apr_get_os_error(), NULL,
                         APLOGNO(02652) "ChangeServiceConfig failed");