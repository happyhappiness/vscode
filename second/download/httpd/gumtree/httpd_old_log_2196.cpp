ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock (%s) (%d)",
                     ap_lock_fname, ap_accept_lock_mech);