ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "%s: Failed to add the RunServices registry entry.",
                         mpm_display_name);