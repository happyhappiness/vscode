ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: Could not set permissions on "
                     "rewrite_log_lock; check User and Group directives");