ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server,
                             "Child %ld failed to acquire lock",
                             (long int)getpid());