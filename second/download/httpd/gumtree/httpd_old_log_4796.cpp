ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "%s: Failed to store the ConfigArgs in the registry.",
                     mpm_display_name);