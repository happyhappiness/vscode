ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "don't know how to spawn child process: %s",
                      r->filename);