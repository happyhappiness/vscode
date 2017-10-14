ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL, 
                     APLOGNO(10012) "Failed to open the '%s' service",
                     mpm_display_name);