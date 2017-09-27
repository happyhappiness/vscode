ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, apr_get_os_error(), NULL,
                     "Query of Service %s failed", mpm_display_name);