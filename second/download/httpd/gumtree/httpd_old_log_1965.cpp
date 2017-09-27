ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
                     "mod_rewrite: Parent could not set permissions "
                     "on RewriteLock; check User and Group directives");