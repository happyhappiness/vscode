ap_log_error(APLOG_MARK, APLOG_ERR, rs, r->server, APLOGNO(02996)
                         "Child %ld failed to try and acquire lock",
                         (long int)getpid());