ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                     "mod_rewrite: Parent could not create RewriteLock "
                     "file %s", lockname);