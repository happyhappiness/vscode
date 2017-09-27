ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                 "Couldn't set permissions on the %s mutex; "
                 "check User and Group directives",
                 type);