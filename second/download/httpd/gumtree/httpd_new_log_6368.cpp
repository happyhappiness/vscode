ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP,
                     apr_get_os_error(), NULL,
                     APLOGNO(10014) "Failed to open the '%s' service",
                     mpm_display_name);