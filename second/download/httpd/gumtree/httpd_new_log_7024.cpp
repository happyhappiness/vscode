ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                     apr_get_os_error(), NULL,
                     APLOGNO(10013)  "Failed to open the Windows service "
                     "manager, perhaps you forgot to log in as Adminstrator?");