ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv2, NULL,
                         "%s: Failed to remove the service config from the "
                         "registry.", mpm_display_name);