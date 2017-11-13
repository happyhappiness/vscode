ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_ENOPROC, r,
               "couldn't setup child process: %s", r->filename);