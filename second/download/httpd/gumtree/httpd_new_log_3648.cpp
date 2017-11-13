ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, r->server,
                     "Child %ld camping out on mutex for %" APR_INT64_T_FMT
                     " microseconds",
                     (long int) getpid(), timecamped);