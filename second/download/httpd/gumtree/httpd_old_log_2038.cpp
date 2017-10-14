ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
                     "Failed to open ticket key file %s: (%d) %pm",
                     path, rv, &rv);