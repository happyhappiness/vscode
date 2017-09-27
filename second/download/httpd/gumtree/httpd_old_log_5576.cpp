ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "unable to create or access scoreboard \"%s\" "
                     "(name-based shared memory failure)", fname);