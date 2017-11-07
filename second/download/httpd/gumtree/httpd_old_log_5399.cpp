ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server,
                         "Child %ld failed to try and acquire lock",
                         (long int)getpid());