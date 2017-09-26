ap_log_error(APLOG_MARK, APLOG_EMERG, errno,
                         NULL, "ufork: Possible mis-configuration "
                         "for user %s - Aborting.", user);