ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "couldn't spawn child process: %s", r->filename);